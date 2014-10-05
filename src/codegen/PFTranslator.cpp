/*
 * PFTranslator.cpp
 *
 *  Created on: Jul 14, 2014
 *      Author: yiwu
 */

#include <cassert>
#include <iostream>
#include "../predecl/PreDecl.h"
#include "../predecl/MatrixStackFuncDecl.h"

#include "PFTranslator.h"

namespace swift {
namespace codegen {

const int PFTranslator::TOTAL_NUM_PARTICLES = Translator::TOTAL_NUM_SAMPLES;

const std::string PFTranslator::StaticClsName = "BLOG_Static_State";
const std::string PFTranslator::TemporalClsName = "BLOG_Temporal_State";
const std::string PFTranslator::MAIN_CLEAR_FUN_NAME = "_clear_marks";
const std::string PFTranslator::TIMESTEP_LIMIT_VAR_NAME = "_TimeLim_";
const std::string PFTranslator::PARTICLE_NUM_VAR_NAME = "_ParticleN_";
const std::string PFTranslator::DEPEND_NUM_VAE_NAME = "_DependN_";
const std::string PFTranslator::STAT_MEMO_VAR_NAME = "_stat_memo";
const std::string PFTranslator::TEMP_MEMO_VAR_NAME = "_temp_memo";
const std::string PFTranslator::PTR_STAT_MEMO_VAR_NAME = "_ptr_stat_memo";
const std::string PFTranslator::PTR_TEMP_MEMO_VAR_NAME = "_ptr_temp_memo";
const std::string PFTranslator::PTR_BACKUP_VAR_NAME = "_ptr_backup";
const TYPE PFTranslator::STAT_MEMO_TYPE = code::Type(StaticClsName,false,false);
const TYPE PFTranslator::REF_STAT_MEMO_TYPE = code::Type(StaticClsName, true, false);
const TYPE PFTranslator::TEMP_MEMO_TYPE = code::Type(TemporalClsName, false, false);
const TYPE PFTranslator::REF_TEMP_MEMO_TYPE = code::Type(TemporalClsName, true, false);
const TYPE PFTranslator::PTR_TEMP_MEMO_TYPE = code::Type(TemporalClsName, false, true);
// Global Variable Names for Particle Filtering
const std::string PFTranslator::CUR_STATE_VAR_NAME = "_cur_state";
const std::string PFTranslator::CUR_TIMESTEP_VAR_NAME = "_cur_time";
// Temporary Local Variable Names
const std::string PFTranslator::TMP_LOOP_VAR_NAME = "_i";
const std::string PFTranslator::TMP_LOCAL_TS_INDEX_VAR_NAME = "_tmp_idx";
// Special Util Funciton for PF
const std::string PFTranslator::PF_RESAMPLE_FUN_NAME = "resample";
const std::string PFTranslator::PF_NORMALIZE_LOGWEI_FUN_NAME = "normalizeLogWeights";
const std::string PFTranslator::PF_COPY_PTR_FUN_NAME = "pointer_copy";
// Special Util data structure for PF to store temporal evidence/query/print
const std::string PFTranslator::TMP_EVI_STORE_NAME = "_evidenceTable";
const code::Type PFTranslator::TMP_EVI_STORE_TYPE("std::function<bool(double&)>");
const std::string PFTranslator::TMP_EVI_INIT_FUNC_NAME = "setup_temporal_evidences";
const std::string PFTranslator::TMP_QUERY_STORE_NAME = "_queryTable";
const code::Type PFTranslator::TMP_QUERY_STORE_TYPE("std::function<void(double)>");
const std::string PFTranslator::TMP_QUERY_INIT_FUNC_NAME = "setup_temporal_queries";
const std::string PFTranslator::TMP_PRINT_STORE_NAME = "_printTable";
const code::Type PFTranslator::TMP_PRINT_STORE_TYPE("std::function<void(void)>");
const std::string PFTranslator::TMP_PRINT_INIT_FUNC_NAME = "setup_temporal_prints";

///////////////////////////////////////////////////////////////
//  Util Functions for Particle Filtering
///////////////////////////////////////////////////////////////
code::Stmt* PFTranslator::referStaticStateStmt(code::DeclContext* context) {
  return new code::DeclStmt(new code::VarDecl(context, CUR_STATE_VAR_NAME, REF_STAT_MEMO_TYPE,
      new code::ArraySubscriptExpr(new code::Identifier(STAT_MEMO_VAR_NAME),
                                   new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME))));
}

code::Stmt* PFTranslator::referTempStateStmt(code::DeclContext* context, std::string tempArg) {
  code::Expr* TS_loc = new code::BinaryOperator(
    new code::Identifier(tempArg), new code::Identifier(DEPEND_NUM_VAE_NAME), code::OpKind::BO_MOD);
  return new code::DeclStmt(new code::VarDecl(context, CUR_STATE_VAR_NAME, REF_TEMP_MEMO_TYPE,
    new code::BinaryOperator(
      NULL,
      new code::ArraySubscriptExpr(
        new code::ArraySubscriptExpr(new code::Identifier(PTR_TEMP_MEMO_VAR_NAME), 
                                   new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME)),
        TS_loc),
      code::OpKind::UO_DEREF)));
}

code::Expr* PFTranslator::referVarFromState(code::Expr* var) {
  return new code::BinaryOperator(new code::Identifier(CUR_STATE_VAR_NAME), var, code::OpKind::BO_FIELD);
}

code::ForStmt* PFTranslator::createForeachLoop(std::string loop_var, std::string loop_n, code::Stmt* body, 
      bool isVarDefined, bool isLess) {
  code::Stmt* init = NULL;
  if (isVarDefined)  
    init = new code::BinaryOperator(new code::Identifier(loop_var),new code::IntegerLiteral(0),code::OpKind::BO_ASSIGN);
  else
    init = new code::DeclStmt(new code::VarDecl(NULL, loop_var, INT_TYPE, new code::IntegerLiteral(0)));
  return new code::ForStmt(init,
    new code::BinaryOperator(new code::Identifier(loop_var),new code::Identifier(loop_n),
                             (isLess ? code::OpKind::BO_LT : code::OpKind::BO_LEQ)),
    new code::BinaryOperator(new code::Identifier(loop_var),NULL,code::OpKind::UO_INC),
    body);
}

code::Expr* PFTranslator::createVarPlusDetExpr(std::string varName, int det) {
  if (det == 0) 
    return new code::Identifier(varName);
  code::OpKind opr = (det > 0 ? code::OpKind::BO_PLUS : (det = -det, code::OpKind::BO_MINUS));
  return new code::BinaryOperator(new code::Identifier(varName), new code::IntegerLiteral(det), opr);
}

bool PFTranslator::isTemporalType(code::Type ty) {
  return ty.getName() == ir::IRConstString::TIMESTEP;
}

/*
 * ==> table[ts]
 */
code::Expr* PFTranslator::tempTableEntryRefer(std::string table, int ts) {
  code::Expr* ind;
  if (ts < 0) ind = new code::Identifier(CUR_TIMESTEP_VAR_NAME);
  else ind = new code::IntegerLiteral(ts);
  code::Expr* entry = new code::ArraySubscriptExpr(new code::Identifier(table), ind);
  return entry;
}

// Special Utils for Liu-West Filter
std::set<std::string> PFTranslator::obsFuncStore = std::set<std::string>();
const std::string PFTranslator::DOUBLE_PERTURB_FUN_NAME = "__perturb";
const std::string PFTranslator::MATRIX_PERTURB_FUN_NAME = "__perturb_matrix";

/////////////// END of Util Functions ///////////////////

PFTranslator::PFTranslator() {
  Translator();
  coreStaticCls = NULL;
  coreTemporalCls = NULL;
  coreTemporalClsClear = NULL;
}

void PFTranslator::translate(std::shared_ptr<swift::ir::BlogModel> model) {
  this->model = model;

  // Special Check for Matrix Usage
  if (model->isUseMatrix())
    prog->addOption("matrix");

  ModelDependency = model->getMarkovOrder();
  ModelTimeLimit = model->getTempLimit();

  if (coreStaticCls == NULL) {
    // add global constant values
    coreNs->addDecl(new code::VarDecl(coreNs,
      PARTICLE_NUM_VAR_NAME, INT_CONST_TYPE, new code::IntegerLiteral(TOTAL_NUM_PARTICLES)));
    coreNs->addDecl(new code::VarDecl(coreNs,
      TIMESTEP_LIMIT_VAR_NAME, INT_CONST_TYPE, new code::IntegerLiteral(ModelTimeLimit)));
    coreNs->addDecl(new code::VarDecl(coreNs,
      DEPEND_NUM_VAE_NAME, INT_CONST_TYPE, new code::IntegerLiteral(ModelDependency + 1)));

    // create Data Structure for Memorization of Particles
    coreStaticCls = code::ClassDecl::createClassDecl(coreNs, StaticClsName);
    coreTemporalCls = code::ClassDecl::createClassDecl(coreNs, TemporalClsName);
    
    /*
    translated code for basic data structures looks like:
      Static_State stat_memo[SampleN];
      Temp_State temp_memo[SampleN][Dependency];
      Static_State* ptr_stat_memo[SampleN];
      Temp_State* ptr_temp_memo[SampleN][Dependency];
      Temp_State* backup_ptr[SampleN][Dependency];
    */
    // Basic Memorization Data Structure for variables
    code::VarDecl::createVarDecl(coreNs, STAT_MEMO_VAR_NAME, 
      std::vector<EXPR>({ new code::Identifier(PARTICLE_NUM_VAR_NAME) }), STAT_MEMO_TYPE);
    code::VarDecl::createVarDecl(coreNs, PTR_STAT_MEMO_VAR_NAME,
      std::vector<EXPR>({ new code::Identifier(PARTICLE_NUM_VAR_NAME) }), STAT_MEMO_TYPE);
    code::VarDecl::createVarDecl(coreNs, TEMP_MEMO_VAR_NAME,
      std::vector<EXPR>({ new code::Identifier(PARTICLE_NUM_VAR_NAME), 
                          new code::Identifier(DEPEND_NUM_VAE_NAME) }), TEMP_MEMO_TYPE);
    // Pointer to Memorization Data Structures
    code::VarDecl::createVarDecl(coreNs, PTR_TEMP_MEMO_VAR_NAME,
      std::vector<EXPR>({ new code::Identifier(PARTICLE_NUM_VAR_NAME),
                          new code::Identifier(DEPEND_NUM_VAE_NAME) }), PTR_TEMP_MEMO_TYPE);
    code::VarDecl::createVarDecl(coreNs, PTR_BACKUP_VAR_NAME,
      std::vector<EXPR>({ new code::Identifier(PARTICLE_NUM_VAR_NAME),
                          new code::Identifier(DEPEND_NUM_VAE_NAME)}), PTR_TEMP_MEMO_TYPE);

    // create Init Method
    createInit();
  }

  // translate type and distinct symbols;
  for (auto ty : model->getTypes())
    transTypeDomain(ty);

  // Check Constant Values
  constValTable.clear();
  for (auto fun : model->getFixFuncs())
    checkConstValue(fun);

  // translate fixed function
  for (auto fun : model->getFixFuncs())
    transFun(fun);

  // translate random function
  for (auto fun : model->getRandFuncs())
    transFun(fun);

  // translate evidence
  transAllEvidence(model->getEvidences());
  
  transSampleAlg();
  
  transAllQuery(model->getQueries());
  
  createMain();
}

code::Code* PFTranslator::getResult() {
  useTag = true;
  return prog;
}

code::FunctionDecl* PFTranslator::transSampleAlg() {
  // only support classical particle filtering here
  // declare the sample method within coreCls
  SAMPLEFUN fun = DECLARE_SAMPLEFUN();
  fun->addStmt(
      new code::DeclStmt(
          new code::VarDecl(fun, WEIGHT_VAR_REF_NAME, DOUBLE_TYPE)));
  // declaring weight field in the class
  // ::: => double weight[PARTICLE_NUM_VAR_NAME];
  code::VarDecl::createVarDecl(coreNs, GLOBAL_WEIGHT_VARNAME,
    std::vector<code::Expr*>({ new code::Identifier(PARTICLE_NUM_VAR_NAME) }),
    DOUBLE_TYPE);
  //call the initialization function
  //   ::: => init()
  fun->addStmt(
      new code::CallExpr(new code::Identifier(MAIN_INIT_FUN_NAME)));
  //call the initialization function for all static Memorization Data Structure
  //   ::: => for(cur_loop = 0; cur_loop < particleN; ++ cur_loop) stat_memo[cur_loop].init();
  fun->addStmt(createForeachLoop(CURRENT_SAMPLE_NUM_VARNAME,PARTICLE_NUM_VAR_NAME,
    code::CallExpr::createMethodCall(
      new code::ArraySubscriptExpr(new code::Identifier(STAT_MEMO_VAR_NAME), new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME)),
      MAIN_INIT_FUN_NAME),true));
  
  /*
    :::=>
    for (cur_t = 0; cur_t <= TimeLimit; cur_t ++) {
      int ind_t = cur_t % Depend;
      copy_pointer(ptr_temp_memo[ind_t], temp_memo[ind_t], ParticleN);
      for (cur_loop = 0; cur_loop < ParticleN; ++ cur_loop) {
        if (set_evidence(local_weight))
          evaluate_query(local_weight);
        weight[cur_loop]=local_weight;
      }
      print();
      (optional, if compute in log_likeli) normalizeLogWeights<SampleN>(weight);
      resample(...);
      (optional) [pertubations ... ]
    }
  */
  // body of cur_t for-loop
  code::CompoundStmt* body_time = new code::CompoundStmt();
  fun->addStmt(createForeachLoop(CUR_TIMESTEP_VAR_NAME, TIMESTEP_LIMIT_VAR_NAME, body_time,true,false));

  // :::=> int ind_t = cur_t % Depend
  body_time->addStmt(new code::DeclStmt(
      new code::VarDecl(NULL,TMP_LOCAL_TS_INDEX_VAR_NAME,INT_TYPE,
        new code::BinaryOperator(new code::Identifier(CUR_TIMESTEP_VAR_NAME),
                                 new code::Identifier(DEPEND_NUM_VAE_NAME),code::OpKind::BO_MOD))));
  // :::=> pointer_copy<_ParticleN_,_DependN_>(_tmp_idx,_ptr_temp_memo,_temp_memo);
  body_time->addStmt(new code::CallTemplateExpr(new code::Identifier(PF_COPY_PTR_FUN_NAME),
    std::vector<code::Expr*>({ 
      new code::Identifier(PARTICLE_NUM_VAR_NAME), 
      new code::Identifier(DEPEND_NUM_VAE_NAME)
    }),
    std::vector<code::Expr*>({
      new code::Identifier(TMP_LOCAL_TS_INDEX_VAR_NAME),
      new code::Identifier(PTR_TEMP_MEMO_VAR_NAME),
      new code::Identifier(TEMP_MEMO_VAR_NAME)
    })));
  // body of cur_loop for-loop
  code::CompoundStmt* body_loop = new code::CompoundStmt();
  body_time->addStmt(createForeachLoop(CURRENT_SAMPLE_NUM_VARNAME, PARTICLE_NUM_VAR_NAME, body_loop, true));
  // :::=> if (set_evidence(weight))
  //           evaluate_query(weight);
  code::CallExpr* set_evi = new code::CallExpr(
    new code::Identifier(SET_EVIDENCE_FUN_NAME),
    std::vector<code::Expr*>{new code::Identifier(WEIGHT_VAR_REF_NAME)});
  code::CallExpr* eval_q = new code::CallExpr(
    new code::Identifier(QUERY_EVALUATE_FUN_NAME),
    std::vector<code::Expr*>{new code::Identifier(WEIGHT_VAR_REF_NAME)});
  body_loop->addStmt(new code::IfStmt(set_evi,eval_q));
  // :::==> weight[current_loop] = w;
  body_loop->addStmt(
      new code::BinaryOperator(
          new code::ArraySubscriptExpr(
              new code::Identifier(GLOBAL_WEIGHT_VARNAME),
              new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME)),
          new code::Identifier(WEIGHT_VAR_REF_NAME), code::OpKind::BO_ASSIGN));
  
  // :::==> print();
  body_time->addStmt(new code::CallExpr(new code::Identifier(ANSWER_PRINT_METHOD_NAME)));

  if (COMPUTE_LIKELIHOOD_IN_LOG) {
    /*
     * :::=>
     *  normalizeLogWeights<SampleN>(weight);
     */
    body_time->addStmt(
      new code::CallTemplateExpr(
        new code::Identifier(PF_NORMALIZE_LOGWEI_FUN_NAME),
        std::vector<code::Expr*>({new code::Identifier(PARTICLE_NUM_VAR_NAME)}),
        std::vector<code::Expr*>({new code::Identifier(GLOBAL_WEIGHT_VARNAME)})));
  }

  /* :::=> 
    resample<SampleN,Dependency,Static_State,Temp_State>(
      weight, stat_memo, ptr_stat_memo,
      ptr_temp_memo, backup_ptr);
  */
  body_time->addStmt(new code::CallTemplateExpr(
    new code::Identifier(PF_RESAMPLE_FUN_NAME),
    std::vector<code::Expr*>({
      new code::Identifier(PARTICLE_NUM_VAR_NAME),
      new code::Identifier(DEPEND_NUM_VAE_NAME)}),
    std::vector<code::Expr*>({
      new code::Identifier(GLOBAL_WEIGHT_VARNAME), 
      new code::Identifier(STAT_MEMO_VAR_NAME), new code::Identifier(PTR_STAT_MEMO_VAR_NAME),
      new code::Identifier(PTR_TEMP_MEMO_VAR_NAME), new code::Identifier(PTR_BACKUP_VAR_NAME)}))
  );

  // Perturbation for Liu-West Filter
  for (auto& func : model->getRandFuncs()) {
    if (func->isTemporal() || obsFuncStore.count(func->getName()) > 0) continue;
    std::string perturb_fun = "";
    if (func->getRetTyp()->getTyp() == ir::IRConstant::DOUBLE)
      perturb_fun = DOUBLE_PERTURB_FUN_NAME;
    else
    if (func->getRetTyp()->getTyp() == ir::IRConstant::MATRIX)
      perturb_fun = MATRIX_PERTURB_FUN_NAME;
    if (perturb_fun.size() == 0) continue; // we can only perturb matrix/double variables

    // TODO: currently perturbation is a hack implementation!!!!!  @Issue
    if (func->argSize() > 2) {
      std::cerr << "[PFTranslator] warning: currently perturbation for liu-west filter \
                   only supports random variables with no more than 2 arguments.  " <<
                   "< " << func->getName() << " >" << std::endl;
      continue;
    }
    bool pb_ok = true; 
    for (size_t i = 0; i < func->argSize() && pb_ok; ++i) {
      auto ty = dynamic_cast<const ir::NameTy*>(func->getArg(i)->getTyp());
      if (ty == NULL || ty->getRefer()->getNumberStmtSize() > 0) {
        pb_ok = false;
        std::cerr << "[PFTranslator] warning: currently perturbation for liu-west filter \
                                        only supports random variables with Name Type without number statement. " <<
                                        "< " << func->getName() << " ( arg#"<< i << ") >" << std::endl;
        break;
      }
    }
    if (!pb_ok) continue;

    // Call Perturbation Method
    if (func->argSize() > 0)
      perturb_fun += "_dim" + std::to_string(func->argSize());
    body_time->addStmt(new code::CallExpr(
      new code::Identifier(perturb_fun),
      std::vector<code::Expr*>({ new code::Identifier(func->getName()) }))
    );
  }
  return fun;
  //TODO adding other algorithms
}

void PFTranslator::transTypeDomain(std::shared_ptr<ir::TypeDomain> td) {
  const std::string& name = td->getName();
  // create a vector containing all the names of its distinct instances
  if (td->getInstNames().size() > 0) {
    std::string arrName = getInstanceStringArrayName(name);
    std::vector<code::Expr*> names;
    for (auto& n : td->getInstNames())
      names.push_back(new code::StringLiteral(n));
    coreNs->addDecl(new code::VarDecl(coreNs, arrName, ARRAY_STRING_CONST_TYPE, 
                                      new code::ListInitExpr(names)));
  }
  // create a class for this declared type
  // and declare a vector to hold all instance in this type
  TYPEDEFN blogtypedefn = DECLARE_TYPE(name);
  // this is the holder for the instances
  std::string inst_var_name = getInstanceArrayName(name);
  // declare fields corresponding to origin functions
  for (auto origin : td->getAllOrigin()) {
    DECLARE_ORIGIN_FIELD(blogtypedefn, origin->getName(),
                         mapIRTypeToCodeType(origin->getTyp()));
  }
  size_t len = td->getPreLen();  // number of predefined distinct symbols
  if (len > 0) {
    // adding distinct symbols
    for (size_t i = 0; i < len; ++i) {
      // :::=>   inst_var_name[i] = "name of the instance";
      code::Stmt* assignst = CREATE_INSTANCE(name, td->getInstName(i));
      coreStaticClsInit->addStmt(assignst); // in StaticMemo
    }
  }
  std::string numvar = getVarOfNumType(name);
  /*
   * TODO: 
   * We currently DO NOT support temporal number statment for typeDomain
   */
  // create a field in the main class:::    int numvar;
  code::FieldDecl::createFieldDecl(coreStaticCls, numvar, INT_TYPE); // in StaticMemo
  // create a field in the main class:::    int mark_numvar;
  std::string marknumvar = getMarkVarName(numvar);
  code::FieldDecl::createFieldDecl(coreStaticCls, marknumvar, INT_TYPE); // in StaticMemo
  // add in the init function:::            numvar = len;
  coreStaticClsInit->addStmt(
      new code::BinaryOperator(new code::Identifier(numvar),
                               new code::IntegerLiteral((int) len),
                               code::OpKind::BO_ASSIGN)); // in StaticMemo
  // add in the init function:::            mark_numvar = -1;
  coreStaticClsInit->addStmt(
      new code::BinaryOperator(new code::Identifier(marknumvar),
                               new code::IntegerLiteral(-1),
                               code::OpKind::BO_ASSIGN)); // in StaticMemo
  // create ensure_num function
  // TODO: yiwu Oct.5.2014
  //   ---> currently a hack. Since we do not allow temporal numberstatement in TimeSeries Model!
  //          So ensure function always locates in the static state
  code::FunctionDecl* ensureFun = code::FunctionDecl::createFunctionDecl(
      coreStaticCls, getEnsureFunName(numvar), VOID_TYPE, true);
  declared_funs[ensureFun->getName()] = ensureFun;
  // add in the init function to call this ensure_fun
  // :::=> ensure_numvar();
  coreStaticClsInit->addStmt(
      new code::CallExpr(new code::Identifier(ensureFun->getName()))); // StaticMemo
  // TODO: 
  //    to support number statement with temporal arguments
  // create the function for getting number of objects in this instance, i.e.
  // numvar
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(
      coreNs, getGetterFunName(numvar), INT_TYPE, true); // Global
  declared_funs[fun->getName()] = fun;

  // add references
  code::Stmt* st = referStaticStateStmt(fun);
  fun->addStmt(st);
  addFunValueRefStmt(fun, marknumvar, std::vector<code::ParamVarDecl*>(), marknumvar, INT_REF_TYPE);
  addFunValueRefStmt(fun, numvar, std::vector<code::ParamVarDecl*>(), numvar, INT_REF_TYPE);

  // handle number statement
  size_t numstlen = td->getNumberStmtSize();
  if (numstlen > 0) {
    code::Stmt* st = new code::IfStmt(
        new code::BinaryOperator(
            new code::Identifier(marknumvar),
            new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME),
            code::OpKind::BO_EQU),
        new code::ReturnStmt(new code::Identifier(numvar)), nullptr);
    fun->addStmt(st);
    // set initial value for number var
    st = new code::BinaryOperator(new code::Identifier(numvar),
                                  new code::IntegerLiteral((int) len),
                                  code::OpKind::BO_ASSIGN);
    fun->addStmt(st);
    // make sure the instance vector contains enough instance
    fun->addStmt(
        code::CallExpr::createMethodCall(
            inst_var_name,
            VECTOR_RESIZE_METHOD_NAME,
            std::vector<code::Expr*>(
                { new code::IntegerLiteral((int) len) })));
    for (size_t k = 0; k < numstlen; k++) {
      // support multiple number statements
      std::string localnumvarname = numvar + std::to_string(k);
      st = new code::DeclStmt(
          new code::VarDecl(fun, localnumvarname, INT_TYPE));
      fun->addStmt(st);
      std::shared_ptr<ir::NumberStmt> numst = td->getNumberStmt(k);
      code::CompoundStmt* insidebody = new code::CompoundStmt();
      // translate the body clause with origin attributes
      st = transClause(numst->getBody(), localnumvarname);
      insidebody->addStmt(st);

      // adjust the number variable's value
      st = new code::BinaryOperator(new code::Identifier(numvar),
                                    new code::Identifier(localnumvarname),
                                    code::OpKind::BO_SPLUS);
      insidebody->addStmt(st);
      // resize the instance vector to make sure it get enough size
      // removed by leili
      //      st = code::CallExpr::createMethodCall(inst_var_name,
      //          VECTOR_RESIZE_METHOD_NAME, std::vector<code::Expr*>( {
      //              new code::Identifier(numvar) }));
      //      insidebody->addStmt(st);
      // append the origin attributes
      std::vector<EXPR> origin_values;
      for (size_t originid = 0; originid < numst->size(); originid++)
        origin_values.push_back(
            new code::Identifier(numst->getVar(originid)->getVarName()));
      st = CREATE_INSTANCE(name, "", origin_values,
                           new code::Identifier(localnumvarname), true); // in getter function
      insidebody->addStmt(st);
      code::Expr* szexp = new code::IntegerLiteral(1);
      st = insidebody;
      // LEILI: TODO: need to set the attributes
      // translate origin attributes
      for (size_t originid = numst->size(); originid > 0;) {
        originid--;
        const ir::OriginAttr* origin = numst->getOrigin(originid);
        auto originvar = numst->getVar(originid);
        // origin type must be nametype
        auto origintypename = origin->getTyp()->toString();
        std::string origin_num_var = getVarOfNumType(origintypename);
        std::string getfun_origin_type = getGetterFunName(origin_num_var);
        // get the number of the origin type
        // :::=>    __get__num_of_type()
        fun->addStmt(
            new code::CallExpr(new code::Identifier(getfun_origin_type)));
        szexp = new code::BinaryOperator(szexp,
                                         new code::Identifier(origin_num_var),
                                         code::OpKind::BO_MUL);
        // set the initial assignment
        // :::=>        int var=0;
        code::Stmt* initst = new code::DeclStmt(
            new code::VarDecl(fun, originvar->getVarName(),
                              mapIRTypeToCodeType(originvar->getTyp()),
                              new code::IntegerLiteral(0)));
        // :::=>        var < _num_of_type
        code::Expr* cond = new code::BinaryOperator(
            new code::Identifier(originvar->getVarName()),
            new code::Identifier(origin_num_var), code::OpKind::BO_LT);
        code::Expr* step = new code::BinaryOperator(
            new code::Identifier(originvar->getVarName()), nullptr,
            code::OpKind::UO_INC);
        st = new code::ForStmt(initst, cond, step, st);
      }

      // for the moment just translate one number statement,
      fun->addStmt(st);
    }
    // call the ensure fun afterwards
    // :::==> ensure_num
    fun->addStmt(
        new code::CallExpr(new code::Identifier(ensureFun->getName())));
    // TODO create functions for number statement and their likelihood
  }
  // markt he markvar
  // ::: => marknumvar = curr_loop
  // TODO: here we assume numberstatment has nothing to do with timestep
  fun->addStmt(
      new code::BinaryOperator(new code::Identifier(marknumvar),
                               createVarPlusDetExpr(CURRENT_SAMPLE_NUM_VARNAME,1),
                               code::OpKind::BO_ASSIGN)); 
  fun->addStmt(new code::ReturnStmt(new code::Identifier(numvar)));
}

void PFTranslator::transFun(std::shared_ptr<ir::FuncDefn> fd) {
  if (fd->isRand()) {
    // translate random function
    // create gettfunname function
    transGetterFun(fd);
    
    // add likelihood function::: double likeli_fun(int, ...);
    transLikeliFun(fd);

    // add setter function::: double set_fun(int, ,,,);
    transSetterFun(fd);
  } else {
    // handle fixed function
    transFixedFun(fd);
  }
}

code::FunctionDecl* PFTranslator::transGetterFun(
    std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string getterfunname = getGetterFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());
  bool isTemp = fd->isTemporal();
  code::ClassDecl* cls = (isTemp ? coreTemporalCls : coreStaticCls);

  // __value__name for recording the value of the function application variable
  std::string valuevarname = getValueVarName(name);
  // adding in the main class a declaration of field for value of a random variable
  addFieldForFunVar(valuevarname, fd->getArgs(), cls, valuetype);
  // __mark__name
  std::string markvarname = getMarkVarName(name);
  // adding in the main class a declaration of field for mark of a random variable
  addFieldForFunVar(markvarname, fd->getArgs(), cls);

  // Note: when adding field, refTag MUST be false!
  // Optimization for Vector/Map/Set Return
  if (valuetype.getName() == ARRAY_BASE_TYPE.getName()
    || valuetype.getName() == MAP_BASE_TYPE.getName()
    || valuetype.getName() == SET_BASE_TYPE.getName()
    || valuetype.getName() == MATRIX_TYPE.getName())
    valuetype.setRef(true);

  // define getter function :::==> __get_value()
  code::FunctionDecl* getterfun = code::FunctionDecl::createFunctionDecl(
      coreNs, getterfunname, valuetype); // Global
  getterfun->setParams(transParamVarDecls(getterfun, fd));
  declared_funs[getterfun->getName()] = getterfun;

  code::Stmt *st = (isTemp ? referTempStateStmt(getterfun,fd->getTemporalArg()->getVarName()) 
                           : referStaticStateStmt(getterfun));
  getterfun->addStmt(st);

  code::Type valueRefType = valuetype;
  if (valuetype != BOOL_TYPE)  // special treatment for bool
    valueRefType.setRef(true);
  addFunValueRefStmt(getterfun, valuevarname, getterfun->getParams(),
                     VALUE_VAR_REF_NAME, valueRefType);
  addFunValueRefStmt(getterfun, markvarname, getterfun->getParams(),
                     MARK_VAR_REF_NAME);
  // now translating::: if (markvar == current sample num) then return value;
  if (isTemp) {
    std::string flagVarName = fd->getTemporalArg()->getVarName();
    st = new code::IfStmt(
      new code::BinaryOperator(new code::Identifier(MARK_VAR_REF_NAME),
      createVarPlusDetExpr(flagVarName, 1), // Mark Current TimeStep if Temporal
      code::OpKind::BO_EQU),
      new code::ReturnStmt(new code::Identifier(VALUE_VAR_REF_NAME)), NULL);
  }
  else {
    /// ::: if (markvar > 0) then return value;
    st = new code::IfStmt(
      new code::BinaryOperator(new code::Identifier(MARK_VAR_REF_NAME),
      new code::IntegerLiteral(0),
      code::OpKind::BO_GT),
      new code::ReturnStmt(new code::Identifier(VALUE_VAR_REF_NAME)), NULL);
  }
  getterfun->addStmt(st);
  // now should sample
  //now translate actual sampling part
  getterfun->addStmt(transClause(fd->getBody(), VALUE_VAR_REF_NAME));
  // now return the value
  // mark the variable first
  // ::: => markvar = cur_loop
  code::Expr* flagVar = (isTemp ? createVarPlusDetExpr(fd->getTemporalArg()->getVarName(), 1)
                                  : new code::IntegerLiteral(1));
  st = new code::BinaryOperator(
       new code::Identifier(MARK_VAR_REF_NAME),
       flagVar,
       code::OpKind::BO_ASSIGN);
  
  getterfun->addStmt(st);
  // special treatment for bool
  if (valuetype == BOOL_TYPE) {
    addFunValueAssignStmt(getterfun, valuevarname, getterfun->getParams(),
                          VALUE_VAR_REF_NAME);
  }
  getterfun->addStmt(
      new code::ReturnStmt(new code::Identifier(VALUE_VAR_REF_NAME)));
  return getterfun;
}

code::FunctionDecl* PFTranslator::transLikeliFun(
    std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string likelifunname = getLikeliFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());
  // __value__name for recording the value of the function application variable
  std::string valuevarname = getValueVarName(name);
  // __mark__name
  std::string markvarname = getMarkVarName(name);
  // adding method declaration in the main class
  code::FunctionDecl* likelifun = code::FunctionDecl::createFunctionDecl(
      coreNs, likelifunname, DOUBLE_TYPE); // Globally defined function
  likelifun->setParams(transParamVarDecls(likelifun, fd));
  declared_funs[likelifun->getName()] = likelifun;

  // Assume current random function has been already sampled!
  bool isTemp = fd->isTemporal();
  code::Stmt* st = (isTemp ? referTempStateStmt(likelifun, fd->getTemporalArg()->getVarName())
                           : referStaticStateStmt(likelifun));
  likelifun->addStmt(st); // refer to current memorization data structure
  // now the value of this function app var is in VALUE_VAR_REF_NAME
  code::Type valueRefType = valuetype;
  if (valuetype != BOOL_TYPE)  // special treatment for bool
    valueRefType.setRef(true);
  addFunValueRefStmt(likelifun, valuevarname, likelifun->getParams(),
                     VALUE_VAR_REF_NAME, valueRefType);
  // declare the weight variable and setting its init value
  // it is recording the log likelihood
  // ::: __weight = 0
  code::VarDecl* weightvar = new code::VarDecl(likelifun, WEIGHT_VAR_REF_NAME,
                                               DOUBLE_TYPE,
                                               new code::FloatingLiteral(0));
  likelifun->addStmt(new code::DeclStmt(weightvar));
  // translate the Clause and calculate weight
  likelifun->addStmt(
      transClause(fd->getBody(), WEIGHT_VAR_REF_NAME, VALUE_VAR_REF_NAME));
  // now return the value
  likelifun->addStmt(
      new code::ReturnStmt(new code::Identifier(WEIGHT_VAR_REF_NAME)));
  return likelifun;
}

code::FunctionDecl* PFTranslator::transSetterFun(
    std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string likelifunname = getLikeliFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());
  // __value__name for recording the value of the function application variable
  std::string valuevarname = getValueVarName(name);
  // __mark__name
  std::string markvarname = getMarkVarName(name);
  std::string setterfunname = getSetterFunName(name);
  // adding setter method declaration in the main class
  code::FunctionDecl* setterfun = code::FunctionDecl::createFunctionDecl(
      coreNs, setterfunname, VOID_TYPE); // Globally defined
  std::vector<code::ParamVarDecl*> args_with_value = transParamVarDecls(
      setterfun, fd);
  declared_funs[setterfun->getName()] = setterfun;

  // Memorization State
  bool isTemp = fd->isTemporal();
  code::Stmt* st = (isTemp ? referTempStateStmt(setterfun, fd->getTemporalArg()->getVarName())
                           : referStaticStateStmt(setterfun));
  setterfun->addStmt(st);

  addFunValueAssignStmt(setterfun, valuevarname, args_with_value,
                        VALUE_ARG_NAME);
  addFunValueRefStmt(setterfun, markvarname, args_with_value,
                     MARK_VAR_REF_NAME);
  // set the argument of setter function
  args_with_value.push_back(
      new code::ParamVarDecl(setterfun, VALUE_ARG_NAME, valuetype));
  setterfun->setParams(args_with_value);

  code::Expr* flagVar = (isTemp ? createVarPlusDetExpr(fd->getTemporalArg()->getVarName(),1) 
                                  : new code::IntegerLiteral(1));
  st = new code::BinaryOperator(
      new code::Identifier(MARK_VAR_REF_NAME),
      flagVar, // when temporal, mark by timestep
      code::OpKind::BO_ASSIGN);
  setterfun->addStmt(st);
  // :::==> value_var = value_arg
  std::vector<code::Expr*> args_ref;
  if (fd->isTemporal())
    args_ref.push_back(new code::Identifier(fd->getTemporalArg()->getVarName()));
  for (auto a : fd->getArgs()) {
    args_ref.push_back(new code::Identifier(a->getVarName()));
  }
  return setterfun;
}

code::FunctionDecl* PFTranslator::transFixedFun(
  std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string fixedfunname = getFixedFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());

  // special check to translate to const value instead of a function
  if (fd->argSize() == 0 && constValTable.count(fixedfunname) > 0) {
    code::FieldDecl::createVarDecl(
      coreNs, fixedfunname, code::Type(fd->getRetTyp()->toString(), false, false, true),
      transExpr(std::dynamic_pointer_cast<ir::Expr>(fd->getBody())));
    return NULL;
  }

  // adding method declaration in the main class
  code::FunctionDecl* fixedfun = code::FunctionDecl::createFunctionDecl(
    coreNs, fixedfunname, valuetype);
  fixedfun->setParams(transParamVarDecls(fixedfun, fd));
  declared_funs[fixedfun->getName()] = fixedfun;
  
  if (std::dynamic_pointer_cast<ir::Expr>(fd->getBody()) != nullptr) {
    fixedfun->addStmt(new code::ReturnStmt(transExpr(std::dynamic_pointer_cast<ir::Expr>(fd->getBody()))));
  }
  else {
    code::VarDecl::createVarDecl(fixedfun, VALUE_VAR_REF_NAME, mapIRTypeToCodeType(fd->getBody()->getTyp()));
    fixedfun->addStmt(
      transClause(fd->getBody(), VALUE_VAR_REF_NAME));
    fixedfun->addStmt(new code::ReturnStmt(new code::Identifier(VALUE_VAR_REF_NAME)));
  }
  return fixedfun;
}

code::Stmt* PFTranslator::transClause(std::shared_ptr<ir::Clause> clause,
                                       std::string retvar,
                                       std::string valuevar) {
  std::shared_ptr<ir::Branch> br = std::dynamic_pointer_cast<ir::Branch>(
      clause);
  if (br) {
    return transBranch(br, retvar, valuevar);
  }
  std::shared_ptr<ir::IfThen> ith = std::dynamic_pointer_cast<ir::IfThen>(
      clause);
  if (ith) {
    return transIfThen(ith, retvar, valuevar);
  }
  std::shared_ptr<ir::Expr> expr = std::dynamic_pointer_cast<ir::Expr>(clause);
  if (expr) {
    return new code::BinaryOperator(new code::Identifier(retvar),
                                    transExpr(expr, valuevar),
                                    code::OpKind::BO_ASSIGN);
    // TODO no 100% correct here why??
  }
  //TODO: warning should not reach here
  return NULL;
}

code::ParamVarDecl* PFTranslator::transParamVarDecl(
    code::DeclContext* context, const std::shared_ptr<ir::VarDecl> var) {
  return new code::ParamVarDecl(context, var->getVarName(),
                                mapIRTypeToCodeType(var->getTyp()));
}

std::vector<code::ParamVarDecl*> PFTranslator::transParamVarDecls(
    code::DeclContext* context,
    std::shared_ptr<ir::FuncDefn> fun) {
  std::vector<code::ParamVarDecl*> vds;
  if (fun->isTemporal())
    vds.push_back(transParamVarDecl(context, fun->getTemporalArg()));
  for (auto v : fun->getArgs()) {
    vds.push_back(transParamVarDecl(context, v));
  }
  return vds;
}

code::Stmt* PFTranslator::transMultiCaseBranch(std::shared_ptr<ir::Branch> br,
  std::string retvar,
  std::string valuevar) {
  std::string mpName = MULTI_CASE_MAP_NAME + std::to_string((size_t)(br.get()));
  auto var = br->getVar();
  if (valuevar.size() == 0) {
    // getter function: need to register a const map for indexing
    code::Type baseTy = mapIRTypeToCodeType(var->getTyp(), false, false);
    // Construct the corresponding MapInit Expr
    auto mex = std::make_shared<ir::MapExpr>();
    mex->setFromTyp(br->getCond(0)->getTyp());
    mex->setToTyp(br->getBranch(0)->getTyp());
    for (size_t i = 0; i < br->getConds().size(); ++i) {
      mex->addMap(br->getCond(i), std::make_shared<ir::IntLiteral>(i));
    }
    code::VarDecl::createVarDecl(
      coreNs, mpName, code::Type(MAP_BASE_TYPE, std::vector<code::Type>({ baseTy, INT_TYPE }), false, false, true),
      transMapExpr(mex));
  }
  auto iter = new code::CallExpr(
    new code::BinaryOperator(
    new code::Identifier(mpName), new code::Identifier("find"), code::OpKind::BO_FIELD),
    { transExpr(var) });
  auto indx = new code::BinaryOperator(iter, new code::Identifier("second"), code::OpKind::BO_POINTER);
  code::SwitchStmt* sst = new code::SwitchStmt(indx);
  code::CaseStmt* cst;
  for (size_t i = 0; i < br->size(); i++) {
    cst = new code::CaseStmt(new code::IntegerLiteral(i),
      transClause(br->getBranch(i), retvar, valuevar));
    sst->addStmt(cst);
    sst->addStmt(new code::BreakStmt());
  }
  return sst;
}

code::Stmt* PFTranslator::transBranch(std::shared_ptr<ir::Branch> br,
                                       std::string retvar,
                                       std::string valuevar) {
  code::SwitchStmt* sst = new code::SwitchStmt(transExpr(br->getVar()));
  code::CaseStmt* cst;
  for (size_t i = 0; i < br->size(); i++) {
    cst = new code::CaseStmt(transExpr(br->getCond(i)),
                             transClause(br->getBranch(i), retvar, valuevar));
    sst->addStmt(cst);
    sst->addStmt(new code::BreakStmt());
  }
  return sst;
}

code::Stmt* PFTranslator::transIfThen(std::shared_ptr<ir::IfThen> ith,
                                       std::string retvar,
                                       std::string valuevar) {
  code::Expr* cond = transExpr(ith->getCond());
  code::Stmt* ifcl = transClause(ith->getThen(), retvar, valuevar);
  code::Stmt* elcl = NULL;
  if (ith->getElse())
    elcl = transClause(ith->getElse(), retvar, valuevar);
  return new code::IfStmt(cond, ifcl, elcl);
}

code::Expr* PFTranslator::transExpr(std::shared_ptr<ir::Expr> expr,
                                     std::string valuevar) {
  std::vector<code::Expr*> args;
  bool used = false;
  code::Expr * res = nullptr;
  // Special Check for MatrixExpr
  if (std::dynamic_pointer_cast<ir::MatrixExpr>(expr) != nullptr)
    res = transMatrixExpr(std::dynamic_pointer_cast<ir::MatrixExpr>(expr));
  else {
    for (size_t k = 0; k < expr->argSize(); k++) {
      args.push_back(transExpr(expr->get(k)));
    }
  }
  // warning::: better to put the above code in separate function

  // translate distribution expression
  std::shared_ptr<ir::Distribution> dist = std::dynamic_pointer_cast<
      ir::Distribution>(expr);
  if (dist) {
    // no need to do further process
    return transDistribution(dist, args, valuevar);
  }

  // translate Function call expression
  std::shared_ptr<ir::FunctionCall> fc = std::dynamic_pointer_cast<
      ir::FunctionCall>(expr);
  if (fc) {
    used = true;
    // TimeStep Function Call
    if (fc->isTemporal())
      args.insert(args.begin(), transExpr(fc->getTemporalArg()));
    res = transFunctionCall(fc, args);
  }

  // translate constant symbols
  std::shared_ptr<ir::ConstSymbol> cs = std::dynamic_pointer_cast<
      ir::ConstSymbol>(expr);
  if (cs) {
    res = transConstSymbol(cs);
  }

  // translate Map expression
  std::shared_ptr<ir::MapExpr> mex = std::dynamic_pointer_cast<ir::MapExpr>(
      expr);
  if (mex) {
    res = transMapExpr(mex);
  }

  // translate Variable reference
  std::shared_ptr<ir::VarRefer> vref = std::dynamic_pointer_cast<ir::VarRefer>(
      expr);
  if (vref) {
    res = new code::Identifier(vref->getRefer()->getVarName());
  }

  // translate binary operation and unitary operation
  std::shared_ptr<ir::OprExpr> opexp = std::dynamic_pointer_cast<ir::OprExpr>(
      expr);
  if (opexp) {
    used = true;
    res = transOprExpr(opexp, args);
  }

  // translate Cardinality expression
  std::shared_ptr<ir::CardExpr> cardexp =
      std::dynamic_pointer_cast<ir::CardExpr>(expr);
  if (cardexp) {
    res = transCardExpr(cardexp, valuevar);
  }

  // translate origin function call
  std::shared_ptr<ir::OriginRefer> oriref = std::dynamic_pointer_cast<
      ir::OriginRefer>(expr);
  if (oriref) {
    res = transOriginRefer(oriref, valuevar);
  }

  // translate quantified formula
  std::shared_ptr<ir::QuantForm> form =
      std::dynamic_pointer_cast<ir::QuantForm>(expr);
  if (form != nullptr && args.size() == 1) {
    used = true;
    res = transQuantForm(form, args[0]);
  }

  // translate set expression
  std::shared_ptr<ir::SetExpr> setexp = std::dynamic_pointer_cast<ir::SetExpr>(
      expr);
  if (setexp) {
    res = transSetExpr(setexp);
  }

  // translate array expression
  std::shared_ptr<ir::ArrayExpr> arrexp = std::dynamic_pointer_cast<ir::ArrayExpr>(
    expr);
  if (arrexp != nullptr) {
    used = true;
    res = transArrayExpr(arrexp, args);
  }

  // Special check when a branch returns a fixed expression rather than a distribution
  if (valuevar.size() > 0) {
    res = new code::BinaryOperator(new code::Identifier(valuevar), res, code::OpKind::BO_EQU);
  }

  // TODO translate other expression
  // if valuevar is provided it should be
  if (!used)
    for (auto ag : args)
      delete ag;
  return res;
}

code::Expr* PFTranslator::transOriginRefer(
    std::shared_ptr<ir::OriginRefer> originref, std::string valuevar) {
  code::Expr* res = transExpr(originref->getOriginArg());
  res = ACCESS_ORIGIN_FIELD(originref->getRefer()->getSrc()->getName(), originref->getRefer()->getName(), res);
  
  if (!valuevar.empty()) {
    // everything other than DistributionExpr needs to check the equality to compute the log likelihood
    std::vector<code::Expr*> cmparg;
    cmparg.push_back(new code::Identifier(valuevar));
    cmparg.push_back(res);
    if (COMPUTE_LIKELIHOOD_IN_LOG) {
      res = new code::CallExpr(new code::Identifier(LOG_EQUAL_FUN_NAME),
                               cmparg);
    } else {
      res = new code::BinaryOperator(cmparg[0], cmparg[1],
                                     code::OpKind::BO_EQU);
    }
  }
  return res;
}

code::Expr* PFTranslator::transCardExpr(std::shared_ptr<ir::CardExpr> cardexp,
                                         std::string valuevar) {
  std::shared_ptr<ir::CondSet> setexp = std::dynamic_pointer_cast<ir::CondSet>(
      cardexp->getBody());
  assert(setexp);
  // Note: For CardExpr, we can directly ignore the func field of this SetExpr

  // can only handle conditional set for the moment.
  std::shared_ptr<ir::VarDecl> var = setexp->getVar();
  const ir::NameTy* tp = dynamic_cast<const ir::NameTy*>(var->getTyp());
  assert(tp);
  // can only handle name type for the moment
  std::string tyname = tp->toString();
  std::string numvarname = getVarOfNumType(tyname);
  std::string getnumvarfunname = getGetterFunName(numvarname);

  if (!setexp->getCond()) {
    // empty condition
    // ::: ==> __get_num_var();
    return new code::CallExpr(new code::Identifier(getnumvarfunname));
  }

  // Count the cardinality of a cond set
  //  ::: ==> _count(__get_num_var(), func)
  //  where func is a lambda expression translated from setexp->getCond();
  auto func = new code::LambdaExpr(code::LambdaKind::REF, BOOL_TYPE);
  func->addStmt(new code::ReturnStmt(transExpr(setexp->getCond())));
  std::vector<code::Expr*> args;
  args.push_back(new code::CallExpr(new code::Identifier(getnumvarfunname)));
  args.push_back(func);
  code::Expr* res = new code::CallExpr(new code::Identifier(FILTER_COUNT_NAME),
                                       args);
  if (!valuevar.empty()) {
    // everything other than DistributionExpr needs to check the equality to compute the log likelihood
    std::vector<code::Expr*> cmparg;
    cmparg.push_back(new code::Identifier(valuevar));
    cmparg.push_back(res);
    if (COMPUTE_LIKELIHOOD_IN_LOG) {
      res = new code::CallExpr(new code::Identifier(LOG_EQUAL_FUN_NAME),
                               cmparg);
    } else {
      res = new code::BinaryOperator(cmparg[0], cmparg[1],
                                     code::OpKind::BO_EQU);
    }
  }
  return res;
}

code::Expr* PFTranslator::transSetExpr(std::shared_ptr<ir::SetExpr> e) {
  auto lstset = std::dynamic_pointer_cast<ir::ListSet>(e);
  if (lstset != nullptr) {
    // list set: vector<int> initialization
    //   e.g. vector<int>{1,2,3}
    std::vector<code::Expr*> args;
    for (auto a : lstset->getArgs())
      args.push_back(transExpr(a));
    code::ListInitExpr* lst = new code::ListInitExpr(args);
    return new code::CallClassConstructor(INT_VECTOR_TYPE,
                                          std::vector<code::Expr*>( { lst }));
  }
  auto condset = std::dynamic_pointer_cast<ir::CondSet>(e);
  if (condset == nullptr) {
    // Should not reach here!!
    assert(false);
  }

  std::shared_ptr<ir::VarDecl> var = condset->getVar();
  const ir::NameTy* tp = dynamic_cast<const ir::NameTy*>(var->getTyp());
  assert(tp != NULL);
  std::string tyname = tp->toString();
  std::string numvarname = getVarOfNumType(tyname);
  std::string getnumvarfunname = getGetterFunName(numvarname);
  std::vector<code::Expr*> args;
  args.push_back(new code::CallExpr(new code::Identifier(getnumvarfunname)));

  code::CallExpr* gen_set = NULL;
  if (condset->getCond() == nullptr) {
    gen_set = new code::CallExpr(new code::Identifier(GEN_FULL_SET_NAME), args);
  }
  else {
    auto func = new code::LambdaExpr(code::LambdaKind::REF, BOOL_TYPE);
    func->addParam(
      new code::ParamVarDecl(func, condset->getVar()->getVarName(), INT_TYPE));
    func->addStmt(new code::ReturnStmt(transExpr(condset->getCond())));
    args.push_back(func);

    gen_set = new code::CallExpr(new code::Identifier(FILTER_FUNC_NAME), args);
  }

  if (condset->getFunc() == nullptr) {
    return gen_set;
  }
  else {
    args.clear();
    args.push_back(gen_set);
    auto func = new code::LambdaExpr(code::LambdaKind::REF, mapIRTypeToCodeType(condset->getFunc()->getTyp()));
    func->addParam(
      new code::ParamVarDecl(func, condset->getVar()->getVarName(), INT_TYPE));
    func->addStmt(new code::ReturnStmt(transExpr(condset->getFunc())));
    args.push_back(func);

    // firstly return-type, then input-type
    return new code::CallTemplateExpr(new code::Identifier(APPLY_FUNC_NAME), 
      std::vector<code::Expr*>{
        new code::Identifier(mapIRTypeToCodeType(condset->getFunc()->getTyp()).getName()),
        new code::Identifier(mapIRTypeToCodeType(condset->getVar()->getTyp()).getName())},
      args);
  }
}

/*
 *  Note: Translation Sample 
 *    Input: forall A a : cond(a)
 *    Output:
 *        _forall(__get_num_A(), [&](int a)->bool{return cond(a);})
 */
code::Expr* PFTranslator::transQuantForm(std::shared_ptr<ir::QuantForm> qt, code::Expr* cond) {
  std::string func = qt->isForall() ? FORALL_NAME : EXISTS_NAME;
  auto var = qt->getVar();
  std::string tyname = var->getTyp()->toString();
  std::string numvarname = getVarOfNumType(tyname);
  std::string getnumvarfunname = getGetterFunName(numvarname);
  auto num = new code::CallExpr(new code::Identifier(getnumvarfunname));
  auto lambda = new code::LambdaExpr();
  lambda->setType(BOOL_TYPE);
  lambda->addParam(new code::ParamVarDecl(lambda, var->getVarName(), INT_TYPE));
  lambda->addStmt(new code::ReturnStmt(cond));
  return new code::CallExpr(new code::Identifier(func), std::vector<code::Expr*>{num, lambda});
}

code::Expr* PFTranslator::transMapExpr(std::shared_ptr<ir::MapExpr> mex) {
  std::vector<code::Expr*> args;
  std::vector<code::Expr*> inside;
  code::Type fromType = mapIRTypeToCodeType(mex->getFromTyp());
  code::Type toType = mapIRTypeToCodeType(mex->getToTyp());
  for (size_t i = 0; i < mex->mapSize(); i++) {
    inside.clear();
    inside.push_back(transExpr(mex->getFrom(i)));
    inside.push_back(transExpr(mex->getTo(i)));
    args.push_back(new code::ListInitExpr(inside));
  }
  code::Expr* list = new code::ListInitExpr(args);
  std::vector<code::Expr*> maparg;
  maparg.push_back(list);
  // TODO: just a hack for the moment, need to support templated type natively
  code::Type maptype(MAP_BASE_TYPE, { fromType, toType });
  return new code::CallClassConstructor(maptype, maparg);
}

code::Expr* PFTranslator::transOprExpr(std::shared_ptr<ir::OprExpr> opr,
                                        std::vector<code::Expr*> args) {
  code::OpKind kind;
  // only need two arguments
  switch (opr->getOp()) {
    case ir::IRConstant::EQ:
      kind = code::OpKind::BO_EQU;
      break;
    case ir::IRConstant::NEQ:
      kind = code::OpKind::BO_NEQ;
      break;
    case ir::IRConstant::LE:
      kind = code::OpKind::BO_LEQ;
      break;
    case ir::IRConstant::GE:
      kind = code::OpKind::BO_GEQ;
      break;
    case ir::IRConstant::LT:
      kind = code::OpKind::BO_LT;
      break;
    case ir::IRConstant::GT:
      kind = code::OpKind::BO_GT;
      break;
    case ir::IRConstant::PLUS:
      if (args.size() == 1)
        kind = code::OpKind::UO_PLUS;
      else
        kind = code::OpKind::BO_PLUS;
      break;
    case ir::IRConstant::MINUS:
      if (args.size() == 1)
        kind = code::OpKind::UO_MINUS;
      else
        kind = code::OpKind::BO_MINUS;
      break;
    case ir::IRConstant::MUL:
      kind = code::OpKind::BO_MUL;
      break;
    case ir::IRConstant::DIV:
      kind = code::OpKind::BO_DIV;
      break;
    case ir::IRConstant::POWER:
      kind = code::OpKind::BO_POW;
      break;
    case ir::IRConstant::MOD:
      kind = code::OpKind::BO_MOD;
      break;
    case ir::IRConstant::AND:
      kind = code::OpKind::BO_AND;
      break;
    case ir::IRConstant::OR:
      kind = code::OpKind::BO_OR;
      break;
    case ir::IRConstant::NOT:
      kind = code::OpKind::UO_NEG;
      break;
    case ir::IRConstant::IMPLY:
      assert(false);  // not supported yet
      break;
    case ir::IRConstant::SUB:
    {
      // Special Check for Matrix Computation
      //   (A*B)[2] is not allowed! have to convert to mat(A*B)[2]
      code::Expr* base = args[0];
      if(opr->get(0)->getTyp()->getTyp()==ir::IRConstant::MATRIX) {
        if (std::dynamic_pointer_cast<ir::OprExpr>(opr->get(0)) != nullptr) {
          base = new code::CallClassConstructor(MATRIX_TYPE, std::vector<code::Expr*>{base});
        }
      }
      return new code::ArraySubscriptExpr(base, args[1]);
    }
      break;
    case ir::IRConstant::PARENTHESES:
    {
      code::Expr* base = args[0];
      args.erase(args.begin());
      if (opr->get(0)->getTyp()->getTyp() == ir::IRConstant::MATRIX
        && std::dynamic_pointer_cast<ir::OprExpr>(opr->get(0)) != nullptr)
        base = new code::CallClassConstructor(MATRIX_TYPE, std::vector<code::Expr*>{ base });
      return new code::CallExpr(base, args);
    }
      break;
    default:
      assert(false);
      break;
  }
  // Unary Operator: Left is nullptr
  if (kind == code::OpKind::UO_NEG || kind == code::OpKind::UO_PLUS || kind == code::OpKind::UO_MINUS)
    return new code::BinaryOperator(NULL, args[0], kind);
  // Normal Operator
  return new code::BinaryOperator(args[0], args.size() > 1 ? args[1] : NULL,
                                  kind);
}

code::Expr* PFTranslator::transArrayExpr(std::shared_ptr<ir::ArrayExpr> opr,
  std::vector<code::Expr*> args) {
  std::vector<code::Expr*> sub{ new code::ListInitExpr(args) };
  return new code::CallClassConstructor(mapIRTypeToCodeType(opr->getTyp()),sub);
}

code::Expr* PFTranslator::transMatrixExpr(std::shared_ptr<ir::MatrixExpr> mat) {
  /*
  Construction of Matrix
  1. construct a row vector
  2. construct a col vector
  3. construct a fixed 2-D real matrix
  4. construct a general 2-D real matrix
  */
  std::vector<code::Expr*> args;
  if (mat->isColVec() || mat->isRowVec()) { // row vector / col vector, which could be constructed via vector directly
    for (size_t i = 0; i < mat->argSize(); ++i)
      args.push_back(transExpr(mat->get(i)));
    code::Type matTy = (mat->isColVec() ? MATRIX_COL_VECTOR_TYPE : MATRIX_ROW_VECTOR_TYPE);
    std::vector<code::Expr*> sub{ new code::ListInitExpr(args) };
    code::Expr* container = new code::CallClassConstructor(MATRIX_CONTAINER_TYPE, sub);
    return new code::CallClassConstructor(matTy, std::vector<code::Expr*>{ container });
  }
  // general cases for matrix
  //    matrixExpr = arrays of row matrixExpr
  size_t row = mat->argSize();
  size_t col = 0;
  for (size_t i = 0; i < mat->argSize(); ++i) {
    if (mat->get(i)->argSize() > col)
      col = mat->get(i)->argSize();
  }
  for (size_t i = 0; i < mat->argSize(); ++i) {
    std::shared_ptr<ir::Expr> row = mat->get(i);
    for (size_t j = 0; j < row->argSize(); ++j) {
      args.push_back(transExpr(row->get(j)));
    }
    for (size_t j = row->argSize(); j < col; ++j) {
      args.push_back(new code::IntegerLiteral(0));
    }
  }
  code::Expr* container = new code::CallClassConstructor(MATRIX_CONTAINER_TYPE,
    std::vector<code::Expr*>{new code::ListInitExpr(args)});
  code::Expr* func = new code::CallExpr(new code::Identifier(TO_MATRIX_FUN_NAME),
    std::vector<code::Expr*>{container, new code::IntegerLiteral((int)row), new code::IntegerLiteral((int)col)});
  return func;
}

code::Expr* PFTranslator::transDistribution(
    std::shared_ptr<ir::Distribution> dist, std::vector<code::Expr*> args,
    std::string valuevar) {
  std::shared_ptr<ir::UniformChoiceDistr> ucdist = std::dynamic_pointer_cast<
      ir::UniformChoiceDistr>(dist);
  if (ucdist) {
    // TODO: consider listset

    // special treatment for UniformChoice;
    std::shared_ptr<ir::CondSet> setexp =
        std::dynamic_pointer_cast<ir::CondSet>(ucdist->getBody());
    assert(setexp);
    std::shared_ptr<ir::VarDecl> var = setexp->getVar();
    const ir::NameTy* tp = dynamic_cast<const ir::NameTy*>(var->getTyp());
    assert(tp);
    std::string tyname = tp->toString();
    std::string numvarname = getVarOfNumType(tyname);
    std::string getnumvarfunname = getGetterFunName(numvarname);
    if (setexp->getCond() == nullptr && setexp->getFunc() == nullptr) {
      // if there is no condition
      std::string distvarname = UNIFORM_INT_DISTRIBUTION_NAME
          + std::to_string((size_t) &(dist->getArgs()));
      if (valuevar.empty()) {
        // sample value
        // define a field in the main class corresponding to the distribution
        code::VarDecl::createVarDecl(
            coreNs, distvarname, code::Type(UNIFORM_INT_DISTRIBUTION_NAME));
        // put init just before sampling
        // :::=> dist.init(0, get_num_of_type - 1)
        code::Expr* callinit = code::CallExpr::createMethodCall(
            distvarname,
            DISTRIBUTION_INIT_FUN_NAME,
            std::vector<code::Expr*>(
                { new code::IntegerLiteral(0), new code::BinaryOperator(
                    new code::CallExpr(new code::Identifier(getnumvarfunname)),
                    new code::IntegerLiteral(1), code::OpKind::BO_MINUS) }));
        // :::=> dist.gen()
        code::Expr* callgen = code::CallExpr::createMethodCall(
            distvarname, DISTRIBUTION_GEN_FUN_NAME);
        // :::=> dist.init(...), dist.gen()
        return new code::BinaryOperator(callinit, callgen,
                                        code::OpKind::BO_COMMA);
      } else {
        // calculating likelihood
        // put init just before sampling
        // :::=> dist.init(0, get_num_of_type)
        code::Expr* callinit = code::CallExpr::createMethodCall(
            distvarname,
            DISTRIBUTION_INIT_FUN_NAME,
            std::vector<code::Expr*>(
                { new code::IntegerLiteral(0), new code::BinaryOperator(
                    new code::CallExpr(new code::Identifier(getnumvarfunname)),
                    new code::IntegerLiteral(1), code::OpKind::BO_MINUS) }));
        // :::=> dist.loglikeli()
        code::Expr* calllikeli = code::CallExpr::createMethodCall(
            distvarname,
            COMPUTE_LIKELIHOOD_IN_LOG ?
                DISTRIBUTION_LOGLIKELI_FUN_NAME : DISTRIBUTION_LIKELI_FUN_NAME,
            std::vector<code::Expr*>( { new code::Identifier(valuevar) }));
        // :::=> dist.init(...), dist.loglikeli()
        return new code::BinaryOperator(callinit, calllikeli,
                                        code::OpKind::BO_COMMA);
      }
    } else {
      // TODO
      //    Note: Actually, it is a general way of dynamic initialization
      std::string distvarname = UNIFORM_CHOICE_DISTRIBUTION_NAME
          + std::to_string((size_t) &(dist->getArgs()));
      if (valuevar.empty()) {
        // Sample value from the distribution
        // define a field in the main class corresponding to the distribution
        code::VarDecl::createVarDecl(
            coreNs, distvarname, code::Type(UNIFORM_CHOICE_DISTRIBUTION_NAME));
        // put init just before sampling
        // :::=> dist.init(_filter(...)) or dist.init(_apply(...))
        code::Expr* callinit = code::CallExpr::createMethodCall(
            distvarname, DISTRIBUTION_INIT_FUN_NAME, std::vector<code::Expr*>( {
                transSetExpr(setexp) }));
        // :::=> dist.gen()
        code::Expr* callgen = code::CallExpr::createMethodCall(
            distvarname, DISTRIBUTION_GEN_FUN_NAME);
        // :::=> dist.init(...), dist.gen()
        return new code::BinaryOperator(callinit, callgen,
                                        code::OpKind::BO_COMMA);
      } else {
        // calculating likelihood
        // put init just before sampling
        // :::=> dist.init(_filter(...))
        code::Expr* callinit = code::CallExpr::createMethodCall(
            distvarname, DISTRIBUTION_INIT_FUN_NAME, std::vector<code::Expr*>( {
                transSetExpr(setexp) }));
        // :::=> dist.loglikeli()
        code::Expr* calllikeli = code::CallExpr::createMethodCall(
            distvarname,
            COMPUTE_LIKELIHOOD_IN_LOG ?
                DISTRIBUTION_LOGLIKELI_FUN_NAME : DISTRIBUTION_LIKELI_FUN_NAME,
            std::vector<code::Expr*>( { new code::Identifier(valuevar) }));
        // :::=> dist.init(...), dist.loglikeli()
        return new code::BinaryOperator(callinit, calllikeli,
                                        code::OpKind::BO_COMMA);
      }
    }
  }
  // in some cases, distributions need dynamic initialization!!
  //     e.g. X~Poisson(5) : static
  //          Y~Poisson(X) : dynamic, since X is not fixed
  std::string name = dist->getDistrName();
  std::string distvarname = name + std::to_string((size_t) &(dist->getArgs()));
  if (dist->isArgRandom()) {
    if (valuevar.empty()) {
      // Sample value from the distribution
      // define a field in the main class corresponding to the distribution
      code::VarDecl::createVarDecl(coreNs, distvarname, code::Type(name));
      // put init just before sampling
      // :::=> dist.init(...)
      code::Expr* callinit = code::CallExpr::createMethodCall(
          distvarname, DISTRIBUTION_INIT_FUN_NAME, args);
      // :::=> dist.gen()
      code::Expr* callgen = code::CallExpr::createMethodCall(
          distvarname, DISTRIBUTION_GEN_FUN_NAME);
      // :::=> dist.init(...), dist.gen()
      return new code::BinaryOperator(callinit, callgen, code::OpKind::BO_COMMA);
    } else {
      // calculating likelihood
      // put init just before sampling
      // :::=> dist.init(...)
      code::Expr* callinit = code::CallExpr::createMethodCall(
          distvarname, DISTRIBUTION_INIT_FUN_NAME, args);
      // :::=> dist.loglikeli()
      code::Expr* calllikeli = code::CallExpr::createMethodCall(
          distvarname,
          COMPUTE_LIKELIHOOD_IN_LOG ?
              DISTRIBUTION_LOGLIKELI_FUN_NAME : DISTRIBUTION_LIKELI_FUN_NAME,
          std::vector<code::Expr*>( { new code::Identifier(valuevar) }));
      // :::=> dist.init(...), dist.loglikeli()
      return new code::BinaryOperator(callinit, calllikeli,
                                      code::OpKind::BO_COMMA);
    }
  } else {
    if (valuevar.empty()) {
      // now actual sampling a value from the distribution
      // define a field in the main class corresponding to the distribution
      code::VarDecl::createVarDecl(coreNs, distvarname, code::Type(name));
      //put initialization in coreClasInit
      coreClsInit->addStmt(
          code::CallExpr::createMethodCall(distvarname,
                                           DISTRIBUTION_INIT_FUN_NAME, args));
      // :::==> distribution.gen();
      // the following two lines of code are not used right now, just use the default engine
      //    std::vector<code::Expr *> rd;
      //    rd.push_back(new code::Identifier(RANDOM_ENGINE_VAR_NAME));
      return code::CallExpr::createMethodCall(distvarname,
                                              DISTRIBUTION_GEN_FUN_NAME);
    } else {
      // calculating likelihood
      // :::==> distribution.loglikeli
      std::vector<code::Expr *> args;
      args.push_back(new code::Identifier(valuevar));
      return code::CallExpr::createMethodCall(
          distvarname,
          COMPUTE_LIKELIHOOD_IN_LOG ?
              DISTRIBUTION_LOGLIKELI_FUN_NAME : DISTRIBUTION_LIKELI_FUN_NAME,
          args);
    }
  }
}

void PFTranslator::createInit() {
  // adding setup for
  // 1. member declarations for core class, need valuearray, mark array, ...
  // 2. initialization function to initialize the values (function called in sample(n)
  // 3. print method
  // 4. debug method
  //coreClsConstructor = code::ClassConstructor::createClassConstructor(coreCls);
  coreClsInit = code::FunctionDecl::createFunctionDecl(coreNs,
                                                       MAIN_INIT_FUN_NAME,
                                                       VOID_TYPE);
  // add clear and init method for static and temporal variables
  coreStaticClsInit = code::FunctionDecl::createFunctionDecl(coreStaticCls,
    MAIN_INIT_FUN_NAME,
    VOID_TYPE);
  coreTemporalClsInit = code::FunctionDecl::createFunctionDecl(coreTemporalCls,
    MAIN_INIT_FUN_NAME,
    VOID_TYPE);
  coreTemporalClsClear = code::FunctionDecl::createFunctionDecl(coreTemporalCls,
    MAIN_CLEAR_FUN_NAME,
    VOID_TYPE);

  // add method debug() in main class to print the current state of the possible world
  // TODO add a flag to support debug or not
  coreClsDebug = code::FunctionDecl::createFunctionDecl(coreNs,
                                                        MAIN_DEBUG_METHOD_NAME,
                                                        VOID_TYPE);

  code::VarDecl::createVarDecl(coreNs, CURRENT_SAMPLE_NUM_VARNAME,
                                   INT_TYPE);
  code::VarDecl::createVarDecl(coreNs, CUR_TIMESTEP_VAR_NAME,
                                   TIMESTEP_TYPE);
  code::VarDecl::createVarDecl(coreNs, RANDOM_DEVICE_VAR_NAME,
                                   RANDOM_ENGINE_TYPE);
}

// add the in the class a field variable for a funcappvar with params
void PFTranslator::addFieldForFunVar(
    std::string varname,
    const std::vector<std::shared_ptr<ir::VarDecl> >& params,
    code::ClassDecl* cls,
    code::Type valueType) {
  if (!params.empty()) {
    // currently a hack, since code do not support expression as template
    // argument
    // TODO, change code and make it general
    valueType =
        code::Type(DYNAMICTABLE_CLASS_NAME,
                   std::vector<code::Type>(
                       {valueType, code::Type(std::to_string(params.size()))}));

    for (size_t id = 0; id < params.size(); id++) {
      // the type of a random function could only be nametype
      std::string argtypename = params[id]->toSignature();
      std::string numvarname_for_arg = getVarOfNumType(argtypename);
      // adding in the ensure_size function for value of a random variable
      // :::=> resize(valuevar, id, number_of_instance);
      code::FunctionDecl* ensureFun =
          declared_funs[getEnsureFunName(numvarname_for_arg)];

      // TODO: TypeDomain & NumberStmt for time series
      //   currently ensure function only appears in StaticMemo!
      //  --> here we assume ensureFun is only called by init function of StaticMemo, a hack here!
      if (cls == coreTemporalCls) { // init temporal MEMO
        ensureFun->addStmt(createForeachLoop(TMP_LOOP_VAR_NAME,DEPEND_NUM_VAE_NAME,
          code::CallExpr::createMethodCall(
          new code::ArraySubscriptExpr(
                  new code::ArraySubscriptExpr(new code::Identifier(TEMP_MEMO_VAR_NAME), new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME)),
                  new code::Identifier(TMP_LOOP_VAR_NAME)),
          DYNAMICTABLE_RESIZE_METHOD_NAME,
          std::vector<code::Expr*>({new code::IntegerLiteral((int) id), new code::Identifier(numvarname_for_arg)}))));
      }
      else {
        ensureFun->addStmt(code::CallExpr::createMethodCall(
                           varname, DYNAMICTABLE_RESIZE_METHOD_NAME,
                           std::vector<code::Expr*>(
                           { new code::IntegerLiteral((int)id),
                             new code::Identifier(numvarname_for_arg) })));
      }
    }
  }
  // adding in the main class a declaration of field for value of a random
  // variable
  code::FieldDecl::createFieldDecl(cls, varname, valueType);
}

void PFTranslator::addFunValueRefStmt(
    code::FunctionDecl* fun, std::string valuevarname,
    const std::vector<code::ParamVarDecl*>& valueindex, std::string valuerefname,
    code::Type varType) {
  // the value of this function application variable is stored in
  // valuevarname[index1][index2]...
  // where the index are corresponding to the arguments
  code::Expr* exp = referVarFromState(new code::Identifier(valuevarname));
  for (auto prm : valueindex) {
    // TODO: currently a hack!!!! to prevent timestep variable
    if (!isTemporalType(prm->getType()))
      exp = new code::ArraySubscriptExpr(exp, new code::Identifier(prm->getId()));
  }
//  if (valueindex.empty()) {
//    // void function does not have Parameter Variable ParamVarDecl, but we still need to access the single element
////    exp = new code::ArraySubscriptExpr(exp, new code::IntegerLiteral(0));
//  }

  // assign the function application variable value to valuerefname
  code::VarDecl* retvar = new code::VarDecl(fun, valuerefname, varType, exp);
  code::DeclStmt* dst = new code::DeclStmt(retvar);
  fun->addStmt(dst);
}

void PFTranslator::addFunValueAssignStmt(
    code::FunctionDecl* fun, std::string valuevarname,
    std::vector<code::ParamVarDecl*>& valueindex, std::string valuerefname) {
  // the value of this function application variable is stored in
  // valuevarname[index1][index2]...
  // where the index are corresponding to the arguments
  code::Expr* exp = referVarFromState(new code::Identifier(valuevarname));
  for (auto prm : valueindex) {
    // TODO: currently a hack!!!! to prevent timestep variable
    if (!isTemporalType(prm->getType()))
      exp = new code::ArraySubscriptExpr(exp, new code::Identifier(prm->getId()));
  }
  // assign valuerefname to the function application variable value to
  code::Stmt* dst = new code::BinaryOperator(exp,
                                             new code::Identifier(valuerefname),
                                             code::OpKind::BO_ASSIGN);
  fun->addStmt(dst);
}

void PFTranslator::transEvidence(std::vector<std::vector<code::Stmt*> >&setterFuncs,
                                  std::vector<std::vector<code::Stmt*> >&likeliFuncs,
                                  std::shared_ptr<ir::Evidence> evid, bool transFuncApp) {
  const std::shared_ptr<ir::Expr>& left = evid->getLeft();
  // check whether left is a function application variable
  std::shared_ptr<ir::FunctionCall> leftexp = std::dynamic_pointer_cast<
      ir::FunctionCall>(left);
  // the timestep this evidence should be processed
  int id = 0;
  // Update the random functions associated with observations
  if (leftexp != nullptr) {
    if (leftexp->isTemporal() 
        && std::dynamic_pointer_cast<ir::TimestepLiteral>(leftexp->getTemporalArg())) 
        // Now we only accept timestep literal. This should be checked in Semant!
    {
      id = std::dynamic_pointer_cast<ir::TimestepLiteral>(leftexp->getTemporalArg())->getValue();
    }
    if (leftexp->getRefer()->isRand()) {
      obsFuncStore.insert(leftexp->getRefer()->getName());
    }
  }

  if (leftexp && transFuncApp) {
    // left side of the evidence is a function application
    std::string blogfunname = leftexp->getRefer()->getName();  // the function name in blog model
    std::string setterfunname = getSetterFunName(blogfunname);  // setter function for the blog function predicate
    std::string likelifunname = getLikeliFunName(blogfunname);  // likeli function for the blog function predicate
    std::vector<code::Expr*> args;
    // check special case for timestep functioncall
    if (leftexp->isTemporal())
      args.push_back(transExpr(leftexp->getTemporalArg()));
    // now translate arguments to this setter function
    for (auto a : leftexp->getArgs()) {
      args.push_back(transExpr(a));
    }
    // assign the right side of the evidence to left function application variable
    args.push_back(transExpr(evid->getRight()));
    // call setter function
    setterFuncs[id].push_back(new code::CallExpr(new code::Identifier(setterfunname), args));

    // calculate likelihood
    // :::=> weight += likeli(...);
    // recompute the args
    args.clear();
    if (leftexp->isTemporal())
      args.push_back(transExpr(leftexp->getTemporalArg()));
    for (auto a : leftexp->getArgs()) {
      args.push_back(transExpr(a));
    }
    code::Stmt* st = new code::BinaryOperator(
        new code::Identifier(WEIGHT_VAR_REF_NAME),
        new code::CallExpr(new code::Identifier(likelifunname), args),
        COMPUTE_LIKELIHOOD_IN_LOG ?
            code::OpKind::BO_SPLUS : code::OpKind::BO_SMUL);
    likeliFuncs[id].push_back(st);
    // add checking for infinity
    // :::=> if (isfinite(weight)) weight += ...
    /*
    code::Expr* cond;
    if (COMPUTE_LIKELIHOOD_IN_LOG) {
      cond = new code::CallExpr(
          new code::Identifier(ISFINITE_FUN_NAME), std::vector<code::Expr*>( {
              new code::Identifier(WEIGHT_VAR_REF_NAME) }));
    } else {
      cond = new code::BinaryOperator(new code::Identifier(WEIGHT_VAR_REF_NAME),
                                      new code::FloatingLiteral(0),
                                      code::OpKind::BO_GT);
    }
    */
    // TODO: To polish the following
    // NOTE: Now remove the if statement since we will print rejection terms firstly
    return;
  }

  // check whether left is a cardinality expression
  std::shared_ptr<ir::CardExpr> cardexp =
      std::dynamic_pointer_cast<ir::CardExpr>(left);

  // TODO: remove transFuncApp
  //    Now we have to firstly print all rejection sampling stmts
  //    Then print the likelihood weighing stmts
  //    TransFuncApp is a switch for this
  // TODO: to check whether the cardExpr contains timestep. Now assume NO!
  if (cardexp && !transFuncApp) {
    // translate cardinality evidence
    // check whether the evidence doesnot hold
    code::Expr* cond = new code::BinaryOperator(transCardExpr(cardexp),
                                                transExpr(evid->getRight()),
                                                code::OpKind::BO_NEQ);
    code::Stmt* st = new code::ReturnStmt(new code::BooleanLiteral(false));
    st = new code::IfStmt(cond, st);
    setterFuncs[id].push_back(st);
    return;
  }
  // TODO adding support for other evidence
  // 1. better setting evidence for Cardinality evidence
}

void PFTranslator::transAllEvidence(
    std::vector<std::shared_ptr<ir::Evidence> > evids) {
  /*
  Firstly generate main set_evidence function
  ==>
  bool _set_evidence(double& __local_weight)
  {
  __local_weight=1.0000000;
  if (evidenceTable[_cur_time])
  return evidenceTable[_cur_time](__local_weight);
  return true;
  }
  */
  code::FunctionDecl* main_fun = code::FunctionDecl::createFunctionDecl(
    coreNs, SET_EVIDENCE_FUN_NAME, BOOL_TYPE);
  main_fun->setParams(std::vector<code::ParamVarDecl*>{new code::ParamVarDecl(main_fun, WEIGHT_VAR_REF_NAME, DOUBLE_REF_TYPE)});
  main_fun->addStmt(new code::BinaryOperator(
    new code::Identifier(WEIGHT_VAR_REF_NAME),
    new code::FloatingLiteral(COMPUTE_LIKELIHOOD_IN_LOG ? 0 : 1.0), code::OpKind::BO_ASSIGN));
  code::Expr* cond = tempTableEntryRefer(TMP_EVI_STORE_NAME, -1);
  code::CallExpr* eviCall = new code::CallExpr(tempTableEntryRefer(TMP_EVI_STORE_NAME),
    std::vector<code::Expr*> {new code::Identifier(WEIGHT_VAR_REF_NAME)});
  code::IfStmt* ifstmt = new code::IfStmt(cond, new code::ReturnStmt(eviCall));
  main_fun->addStmt(ifstmt);
  main_fun->addStmt(new code::ReturnStmt(new code::BooleanLiteral(true)));
  /*
  Register data structure to store all the evidences
  ==> std::function<bool(double&)> evidenceTable[_TimeLim_+1];
  ==> void setup_temporal_evidence(){}
  */
  code::VarDecl::createVarDecl(coreNs, TMP_EVI_STORE_NAME,
    std::vector<EXPR>({ 
      new code::BinaryOperator(new code::Identifier(TIMESTEP_LIMIT_VAR_NAME), 
      new code::IntegerLiteral(1), code::OpKind::BO_PLUS) }
    ),TMP_EVI_STORE_TYPE);
  tempEvidenceInit = code::FunctionDecl::createFunctionDecl(
    coreNs, TMP_EVI_INIT_FUNC_NAME, VOID_TYPE);
  // put the init function in the coreInit
  coreClsInit->addStmt(new code::CallExpr(new code::Identifier(TMP_EVI_INIT_FUNC_NAME)));

  // generate all the evidences
  std::vector<std::vector<code::Stmt*> > setterFuncs(model->getTempLimit() + 1);
  std::vector<std::vector<code::Stmt*> > likeliFuncs(model->getTempLimit() + 1);

  //TODO: 
  //  gather timestep information for evidence in Semant
  for (auto evid : evids) {
    // Firstly Translate all rejection sampling stmts
    // TODO:
    //   Now we assume all rejection sampling contain no timestep!!! to add timestep support
    transEvidence(setterFuncs, likeliFuncs, evid, false);
  }

  for (auto evid : evids) {
    // Secondly Translate all likelihood weighing stmts
    std::shared_ptr<ir::FunctionCall> leftexp = std::dynamic_pointer_cast<
      ir::FunctionCall>(evid->getLeft());
    if (leftexp == nullptr) continue; // not likelihood evidence at all!
    transEvidence(setterFuncs, likeliFuncs, evid, true);
  }
  
  /*
   * for each timestep
   * ==> 
   *  evidenceTable[3] = [&](double& __local_weight)->bool {
   *  __local_weight *= __set_O(3, 0);
   *  return true;
   * };
   */
  for (size_t i = 0; i < setterFuncs.size(); ++i) {
    if (setterFuncs[i].size() == 0) continue; // no evidence in this timestep
    auto lamFunc = new code::LambdaExpr(code::LambdaKind::REF,BOOL_TYPE);
    lamFunc->addParam(new code::ParamVarDecl(lamFunc,WEIGHT_VAR_REF_NAME,DOUBLE_REF_TYPE));
    for (auto& st : setterFuncs[i])
      lamFunc->addStmt(st);
    for (auto& st : likeliFuncs[i])
      lamFunc->addStmt(st);
    lamFunc->addStmt(new code::ReturnStmt(new code::BooleanLiteral(true)));
    auto stmt = new code::BinaryOperator(tempTableEntryRefer(TMP_EVI_STORE_NAME,i),
                lamFunc, code::OpKind::BO_ASSIGN);
    tempEvidenceInit->addStmt(stmt);
  }
}

void PFTranslator::transAllQuery(
    std::vector<std::shared_ptr<ir::Query> > queries) {
  // Note:
  //  Assume TimeStep only appears when query->getVar() is temporal FunctionCall
  // TODO:
  //  to parse timestep in general expressions in Semant

  /*
  Firstly generate main evaluate_query function
  ==>
  inline void _evaluate_query(double __local_weight)
  {
    if (queryTable[_cur_time])
      queryTable[_cur_time](__local_weight);
  }
  */
  code::FunctionDecl* main_fun = code::FunctionDecl::createFunctionDecl(
    coreNs, QUERY_EVALUATE_FUN_NAME, VOID_TYPE, true);
  main_fun->setParams(std::vector<code::ParamVarDecl*>{new code::ParamVarDecl(main_fun, WEIGHT_VAR_REF_NAME, DOUBLE_TYPE)});
  code::Expr* cond = tempTableEntryRefer(TMP_QUERY_STORE_NAME, -1);
  code::CallExpr* queryCall = new code::CallExpr(tempTableEntryRefer(TMP_QUERY_STORE_NAME),
    std::vector<code::Expr*> {new code::Identifier(WEIGHT_VAR_REF_NAME)});
  code::IfStmt* ifstmt = new code::IfStmt(cond, queryCall);
  main_fun->addStmt(ifstmt);

  /*
  also generate main answer_print function
  ==>
  void print() {
    if (printTable[_cur_time]) {
      printf("++++++++++++++++ TimeStep @%d ++++++++++++++++\n", _cur_time);
      printTable[_cur_time]();
    }
  }
  */
  coreClsPrint = code::FunctionDecl::createFunctionDecl(
    coreNs, ANSWER_PRINT_METHOD_NAME, VOID_TYPE, true);
  code::Expr* prtcond = tempTableEntryRefer(TMP_PRINT_STORE_NAME, -1);
  code::CallExpr* prtCall = new code::CallExpr(tempTableEntryRefer(TMP_PRINT_STORE_NAME));
  code::CompoundStmt* cmp = new code::CompoundStmt();

  // Output Timestep Counter
  cmp->addStmt(new code::CallExpr( new code::Identifier("printf"),
    std::vector<code::Expr*>{ new code::StringLiteral("++++++++++++++++ TimeStep @%d ++++++++++++++++\\n"), 
                              new code::Identifier(CUR_TIMESTEP_VAR_NAME)})
  );

  cmp->addStmt(prtCall);
  code::IfStmt* prtifstmt = new code::IfStmt(prtcond, cmp);
  coreClsPrint->addStmt(prtifstmt);

  /*
  Register data structure to store all the evidences
  ==> std::function<void(double)> queryTable[_TimeLim_+1];
  ==> std::function<void(void)> printTable[_TimeLim_+1];
  ==> void setup_temporal_query(){}
  ==> void setup_temporal_print(){}
  */
  code::VarDecl::createVarDecl(coreNs, TMP_QUERY_STORE_NAME,
    std::vector<EXPR>({
    new code::BinaryOperator(new code::Identifier(TIMESTEP_LIMIT_VAR_NAME),
    new code::IntegerLiteral(1), code::OpKind::BO_PLUS) }
  ), TMP_QUERY_STORE_TYPE);
  code::VarDecl::createVarDecl(coreNs, TMP_PRINT_STORE_NAME,
    std::vector<EXPR>({
    new code::BinaryOperator(new code::Identifier(TIMESTEP_LIMIT_VAR_NAME),
    new code::IntegerLiteral(1), code::OpKind::BO_PLUS) }
  ), TMP_PRINT_STORE_TYPE);
  tempQueryInit = code::FunctionDecl::createFunctionDecl(
    coreNs, TMP_QUERY_INIT_FUNC_NAME, VOID_TYPE);
  tempPrintInit = code::FunctionDecl::createFunctionDecl(
    coreNs, TMP_PRINT_INIT_FUNC_NAME, VOID_TYPE);

  // put the init function in the coreInit
  coreClsInit->addStmt(new code::CallExpr(new code::Identifier(TMP_QUERY_INIT_FUNC_NAME)));
  coreClsInit->addStmt(new code::CallExpr(new code::Identifier(TMP_PRINT_INIT_FUNC_NAME)));

  // generate all the queries
  std::vector<std::vector<code::Stmt*> > queryFuncs(model->getTempLimit() + 1);
  std::vector<std::vector<code::Stmt*> > printFuncs(model->getTempLimit() + 1);

  int index = 0;
  for (auto qr : queries) {
    transQuery(queryFuncs, printFuncs, qr, index ++);
  }

  /*
  * for each timestep
  * ==>
  *  queryTable[0] = [&](double __local_weight) {
  *   _answer.add(....);
  *  };
  *  printTable[0] = [&]() {
  *    _answer_0.print("query expr"); ...
  *  };
  */
  for (size_t i = 0; i < queryFuncs.size(); ++i) {
    if (queryFuncs[i].size() == 0) continue; // no query in this timestep, and we do not need to print
    // LambdaFunction for Query
    auto queryLambda = new code::LambdaExpr(code::LambdaKind::REF);
    queryLambda->addParam(new code::ParamVarDecl(queryLambda, WEIGHT_VAR_REF_NAME, DOUBLE_TYPE));
    for (auto& st : queryFuncs[i])
      queryLambda->addStmt(st);
    tempQueryInit->addStmt(
      new code::BinaryOperator(tempTableEntryRefer(TMP_QUERY_STORE_NAME, i),
      queryLambda, code::OpKind::BO_ASSIGN));
    // LambdaFunction for Print
    auto printLambda = new code::LambdaExpr(code::LambdaKind::REF);
    for (auto& st : printFuncs[i])
      printLambda->addStmt(st);
    tempPrintInit->addStmt(
      new code::BinaryOperator(tempTableEntryRefer(TMP_PRINT_STORE_NAME, i),
      printLambda, code::OpKind::BO_ASSIGN));
  }
}

void PFTranslator::transQuery(std::vector<std::vector<code::Stmt*> >& queryFuncs,
                               std::vector<std::vector<code::Stmt*> >& printFuncs, 
                               std::shared_ptr<ir::Query> qr, int n) {
  // Register Printer Class
  std::string answervarname = ANSWER_VAR_NAME_PREFIX + std::to_string(n);
  std::vector<code::Expr*> initArgs{ new code::BooleanLiteral(COMPUTE_LIKELIHOOD_IN_LOG) };
  if (dynamic_cast<const ir::NameTy*>(qr->getVar()->getTyp()) != nullptr) {
    auto ty = dynamic_cast<const ir::NameTy*>(qr->getVar()->getTyp());
    std::string tyName = ty->getRefer()->getName();
    initArgs.push_back(new code::StringLiteral(tyName));
    if (ty->getRefer()->getInstNames().size() > 0) {
      initArgs.push_back(new code::BinaryOperator(NULL,
        new code::Identifier(getInstanceStringArrayName(tyName)), code::OpKind::UO_ADDR));
    }
  }
  code::Expr* initvalue = new code::CallClassConstructor(
      code::Type(HISTOGRAM_CLASS_NAME, std::vector<code::Type>( {
          mapIRTypeToCodeType(qr->getVar()->getTyp()) })),
          initArgs);
  code::VarDecl::createVarDecl(
      coreNs, answervarname,
      code::Type(HISTOGRAM_CLASS_NAME, std::vector<code::Type>( {
          mapIRTypeToCodeType(qr->getVar()->getTyp()) })),
      initvalue);
  // The timestep this query should be processed
  int id = 0;
  auto var = qr->getVar();
  if (std::dynamic_pointer_cast<ir::FunctionCall>(var) != nullptr) {
    auto fun = std::dynamic_pointer_cast<ir::FunctionCall>(var);
    if (fun->isTemporal() && std::dynamic_pointer_cast<ir::TimestepLiteral>(fun->getTemporalArg()) != nullptr) {
      // Assume that the Timestep for each query is a fixed value
      //  >> This should be checked in Semant
      id = std::dynamic_pointer_cast<ir::TimestepLiteral>(fun->getTemporalArg())->getValue();
    }
    else {
      if (!fun->isTemporal())
        id = model->getTempLimit();
    }
  }

  std::vector<code::Expr*> args;
  args.push_back(transExpr(qr->getVar()));
  args.push_back(new code::Identifier(WEIGHT_VAR_REF_NAME));
  queryFuncs[id].push_back(code::CallExpr::createMethodCall(answervarname, HISTOGRAM_ADD_METHOD_NAME,
    args));
  
  // add print this result in print()
  // :::=> answer_id.print("query expr");
  printFuncs[id].push_back(
      code::CallExpr::createMethodCall(answervarname,
                                       HISTOGRAM_PRINT_METHOD_NAME,
                                       std::vector<code::Expr*> { new code::StringLiteral(qr->str()) }));
}

code::Expr* PFTranslator::transConstSymbol(
    std::shared_ptr<ir::ConstSymbol> cs) {
  std::shared_ptr<ir::InstSymbolRef> isr = std::dynamic_pointer_cast<
      ir::InstSymbolRef>(cs);
  if (isr) {
    return new code::IntegerLiteral((int) (isr->getInst()->getID()));
  }
  std::shared_ptr<ir::BoolLiteral> bl = std::dynamic_pointer_cast<
      ir::BoolLiteral>(cs);
  if (bl) {
    return new code::BooleanLiteral(bl->getValue());
  }
  std::shared_ptr<ir::DoubleLiteral> dl = std::dynamic_pointer_cast<
      ir::DoubleLiteral>(cs);
  if (dl) {
    return new code::FloatingLiteral(dl->getValue());
  }
  std::shared_ptr<ir::IntLiteral> il =
      std::dynamic_pointer_cast<ir::IntLiteral>(cs);
  if (il) {
    return new code::IntegerLiteral(il->getValue());
  }
  std::shared_ptr<ir::TimestepLiteral> tl =
    std::dynamic_pointer_cast<ir::TimestepLiteral>(cs);
  if (tl) {
    return new code::IntegerLiteral(tl->getValue());
  }
  std::shared_ptr<ir::NullSymbol> nl =
      std::dynamic_pointer_cast<ir::NullSymbol>(cs);
  if (nl) {
    // TODO change the translation of null
    if (nl->getTyp() != NULL && nl->getTyp()->getTyp() == ir::IRConstant::STRING)
      return new code::StringLiteral("<NULL>");
    return new code::IntegerLiteral(NULLSYMBOL_VALUE);
  }
  std::shared_ptr<ir::StringLiteral> sl = std::dynamic_pointer_cast<
      ir::StringLiteral>(cs);
  if (sl) {
    return new code::StringLiteral(sl->getValue());
  }

  assert(false);  // should not reach here
  return nullptr;
}

code::Expr* PFTranslator::transFunctionCall(
    std::shared_ptr<ir::FunctionCall> fc, std::vector<code::Expr*> args) {
  std::string getterfunname;
  // Special Check for builtin functions
  if (fc->isBuiltin()) {
    // Special Check for vstack and hstack
    if (dynamic_cast<const predecl::MatrixStackFuncDecl*>(fc->getBuiltinRefer()) != NULL) {
      auto lst = new code::ListInitExpr(args);
      return new code::CallExpr(new code::Identifier(fc->getBuiltinRefer()->getName()), std::vector<code::Expr*>{lst});
    }
    return new code::CallExpr(new code::Identifier(fc->getBuiltinRefer()->getName()), args);
  }
  switch (fc->getKind()) {
    case ir::IRConstant::RANDOM:
      getterfunname = getGetterFunName(fc->getRefer()->getName());
      return new code::CallExpr(new code::Identifier(getterfunname), args);
    case ir::IRConstant::FIXED:
      getterfunname = getFixedFunName(fc->getRefer()->getName());
      if (constValTable.count(getterfunname) > 0 && args.size() == 0) {
        // This fixed function is actually a constant variable
        return new code::Identifier(getterfunname);
      }
      return new code::CallExpr(new code::Identifier(getterfunname), args);
    default:
      return nullptr;
  }
}

void PFTranslator::createMain() {
  mainFun = code::FunctionDecl::createFunctionDecl(prog, MAIN_FUN_NAME,
                                                   INT_TYPE);

  // for timing
  code::Stmt* st = new code::DeclStmt(
      new code::VarDecl(
          mainFun,
          "__start_time",
          code::Type(std::vector<std::string>( { "std", "chrono" }),
                     "time_point", code::Type(std::vector<std::string>( { "std",
                         "chrono" }),
                                              "system_clock")),
          new code::CallExpr(
              new code::Identifier("std::chrono::system_clock::now"))));
  mainFun->addStmt(st);
  /*
  st = new code::DeclStmt(
      new code::VarDecl(
          mainFun, SAMPLER_VAR_NAME, code::Type(std::vector<std::string>( {
              coreNs->getName() }),
                                                coreCls->getName())));
  mainFun->addStmt(st);
  
  st = code::CallExpr::createMethodCall(SAMPLER_VAR_NAME,
                                        MAIN_SAMPLING_FUN_NAME);
  mainFun->addStmt(st);
  */
  mainFun->addStmt(
    new code::BinaryOperator(new code::Identifier(MAIN_NAMESPACE_NAME), 
    new code::CallExpr(new code::Identifier(MAIN_SAMPLING_FUN_NAME)),code::OpKind::BO_SCOPE)
  );
  // calculate duration
  st = new code::DeclStmt(
      new code::VarDecl(
          mainFun,
          "__elapsed_seconds",
          code::Type(std::vector<std::string>( { "std", "chrono" }), "duration",
                     code::Type("double")),
          new code::BinaryOperator(
              new code::CallExpr(
                  new code::Identifier("std::chrono::system_clock::now")),
              new code::Identifier("__start_time"), code::OpKind::BO_MINUS)));
  mainFun->addStmt(st);

  st = new code::CallExpr(
      new code::Identifier("printf"), std::vector<code::Expr*>( {
          new code::StringLiteral("\\nrunning time: %fs\\n"),
          code::CallExpr::createMethodCall("__elapsed_seconds", "count") }));
  mainFun->addStmt(st);
}

inline TYPEDEFN PFTranslator::DECLARE_TYPE(std::string name) {
  // create a class for this declared type
  TYPEDEFN cd = code::ClassDecl::createClassDecl(coreNs, name);
  code::FieldDecl::createFieldDecl(cd, DISTINCT_FIELDNAME, STRING_TYPE);
  // declare a vector to hold all instance in this type
  std::string inst_var_name = getInstanceArrayName(name);
  code::VarDecl::createVarDecl(
      coreNs,
      inst_var_name,
      code::Type(VECTOR_CLASS_NAME,
                 std::vector<code::Type>( { code::Type(name) })));
  return cd;
}

inline ORIGINDEFN PFTranslator::DECLARE_ORIGIN_FIELD(TYPEDEFN typedf,
                                                      std::string originname,
                                                      TYPE origintype) {
  return code::FieldDecl::createFieldDecl(typedf, originname, origintype);
}

inline STMT PFTranslator::CREATE_INSTANCE(std::string tyname,
                                           std::string instname,
                                           std::vector<EXPR> originvalues,
                                           EXPR ncopy, bool inGetter) {
  // this is the holder for the instances
  std::string inst_var_name = (inGetter ? CUR_STATE_VAR_NAME + "." : "")
                              + getInstanceArrayName(tyname); // need to refer to current state if in getter function
  code::Stmt* st;
  std::vector<code::Expr*> values;
  values.push_back(new code::StringLiteral(instname));
  if (!originvalues.empty())
    values.insert(values.end(), originvalues.begin(), originvalues.end());
  if (ncopy)
    st = new code::CallExpr(
        new code::Identifier(APPEND_FUN_NAME),
        std::vector<EXPR>( { new code::Identifier(inst_var_name), ncopy,
            new code::ListInitExpr(values) }));
  else
    st = code::CallExpr::createMethodCall(
        inst_var_name, VECTOR_ADD_METHOD_NAME, std::vector<code::Expr*>( {
            new code::ListInitExpr(values) }));

  return st;
}
  
inline EXPR PFTranslator::ACCESS_ORIGIN_FIELD(std::string tyname,
                                               std::string originname,
                                               EXPR originarg) {
  // this is the holder for the instances
  std::string inst_var_name = getInstanceArrayName(tyname);
  EXPR exp = new code::ArraySubscriptExpr(new code::Identifier(inst_var_name), originarg);
  exp = new code::BinaryOperator(exp, new code::Identifier(originname), code::OpKind::BO_FIELD);
  return exp;
}

inline SAMPLEFUN PFTranslator::DECLARE_SAMPLEFUN() {
  // declare the sample method within coreNs
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(
      coreNs, MAIN_SAMPLING_FUN_NAME, VOID_TYPE);
  return fun;
}

} /* namespace codegen */
} /* namespace swift */

