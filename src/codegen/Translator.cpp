/*
 * Translator.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include <cassert>
#include "../predecl/PreDecl.h"
#include "../predecl/MatrixStackFuncDecl.h"
#include "../predecl/SetAggrFuncDecl.h"

#include "Translator.h"

namespace swift {
namespace codegen {
swift::Configuration* config = swift::Configuration::getConfiguration();
bool Translator::COMPUTE_LIKELIHOOD_IN_LOG =
    swift::Configuration::getConfiguration()->getBoolValue(
        "COMPUTE_LIKELIHOOD_IN_LOG");

const std::string Translator::VECTOR_CLASS_NAME = "vector";
const std::string Translator::VECTOR_RESIZE_METHOD_NAME = "resize";
const std::string Translator::VECTOR_ADD_METHOD_NAME = "push_back";
const std::string Translator::APPEND_FUN_NAME = "append";
const std::string Translator::DYNAMICTABLE_CLASS_NAME = "DynamicTable";
const std::string Translator::DYNAMICTABLE_RESIZE_METHOD_NAME = "resize";
const code::Type Translator::INT_TYPE("int");
const code::Type Translator::INT_REF_TYPE("int", true);
const code::Type Translator::INT_CONST_TYPE("int", false, false, true);
const code::Type Translator::INT_VECTOR_TYPE(VECTOR_CLASS_NAME,
                                                { INT_TYPE });
const code::Type Translator::DOUBLE_TYPE("double");
const code::Type Translator::DOUBLE_REF_TYPE("double", true);
const code::Type Translator::DOUBLE_VECTOR_TYPE(VECTOR_CLASS_NAME, {
                                                       DOUBLE_TYPE });
const code::Type Translator::STRING_TYPE("string");
const code::Type Translator::CHAR_TYPE("char");
const code::Type Translator::TIMESTEP_TYPE("unsigned");
const code::Type Translator::BOOL_TYPE("bool");
const code::Type Translator::VOID_TYPE("void");

const code::Type Translator::MATRIX_TYPE("mat");
const code::Type Translator::MATRIX_REF_TYPE("mat", true);
const code::Type Translator::MATRIX_CONST_TYPE("mat", false, false, true);
const code::Type Translator::MATRIX_ROW_VECTOR_TYPE("rowvec");
const code::Type Translator::MATRIX_COL_VECTOR_TYPE("vec");
const code::Type Translator::MATRIX_CONTAINER_TYPE("vector<double>");

// TODO: This could be potentially replaced by array
const code::Type Translator::ARRAY_BASE_TYPE("vector");
const code::Type Translator::ARRAY_STRING_CONST_TYPE("vector<string>",false,false,true);
const code::Type Translator::MAP_BASE_TYPE("map");
const code::Type Translator::SET_BASE_TYPE("set");
const std::string Translator::SET_EVIDENCE_FUN_NAME = "_set_evidence";
const std::string Translator::QUERY_EVALUATE_FUN_NAME = "_evaluate_query";
const std::string Translator::DISTINCT_FIELDNAME = "_name";
const std::string Translator::DISTRIBUTION_INIT_FUN_NAME = "init";
const std::string Translator::DISTRIBUTION_GEN_FUN_NAME = "gen";
const std::string Translator::DISTRIBUTION_LIKELI_FUN_NAME = "likeli";
const std::string Translator::DISTRIBUTION_LOGLIKELI_FUN_NAME = "loglikeli";
const std::string Translator::CURRENT_SAMPLE_NUM_VARNAME = "_cur_loop";
const std::string Translator::WEIGHT_VAR_REF_NAME = "__local_weight";
const std::string Translator::GLOBAL_WEIGHT_VARNAME = "_weight";
const std::string Translator::VALUE_VAR_REF_NAME = "__retvalue";
const std::string Translator::VALUE_ARG_NAME = "__retvalue_arg";
const std::string Translator::MARK_VAR_REF_NAME = "__mark";
const std::string Translator::HISTOGRAM_CLASS_NAME = "Hist";
const std::string Translator::HISTOGRAM_ADD_METHOD_NAME = "add";
const std::string Translator::HISTOGRAM_PRINT_METHOD_NAME = "print";
const std::string Translator::LOG_EQUAL_FUN_NAME = "logEqual";
const std::string Translator::ISFINITE_FUN_NAME = "isfinite";
const std::string Translator::NEG_INFINITE_NAME = "-INFINITY";
const std::string Translator::ANSWER_VAR_NAME_PREFIX = "_answer_";
const std::string Translator::ANSWER_PRINT_METHOD_NAME = "print";
const std::string Translator::MAIN_DEBUG_METHOD_NAME = "debug";
const std::string Translator::MAIN_SAMPLING_FUN_NAME = "sample";
const std::string Translator::SAMPLER_VAR_NAME = "sampler";
const std::string Translator::MAIN_NAMESPACE_NAME = "swift";
const std::string Translator::MAIN_INIT_FUN_NAME = "init";
const std::string Translator::MAIN_FUN_NAME = "main";
const std::string Translator::LOCAL_NUM_SAMPLE_ARG_NAME = "n";
const std::string Translator::MULTI_CASE_MAP_NAME = "_multicase_idx";

// randomness
const std::string Translator::RANDOM_DEVICE_VAR_NAME = "__random_device";
const code::Type Translator::RANDOM_ENGINE_TYPE("default_random_engine");
const std::string Translator::RANDOM_ENGINE_VAR_NAME = "__random_engine";
const std::string Translator::UNIFORM_INT_DISTRIBUTION_NAME = "UniformInt";
const std::string Translator::FILL_N_FUN_NAME = "fill_n";
const std::string Translator::UNIFORM_CHOICE_DISTRIBUTION_NAME =
    "UniformChoice";
const int Translator::INIT_SAMPLE_NUM = 0;
const int Translator::NULLSYMBOL_VALUE = -1;
const int Translator::TOTAL_NUM_SAMPLES = 1000000;

// internal predefined functions
const std::string Translator::GEN_FULL_SET_NAME = "_gen_full";
const std::string Translator::APPLY_FUNC_NAME = "_apply";
const std::string Translator::AGGREGATE_FUNC_NAME = "_aggregate";
const std::string Translator::FILTER_FUNC_NAME = "_filter";
const std::string Translator::FILTER_RANGE_FUNC_NAME = "_filter_range";
const std::string Translator::FILTER_COUNT_NAME = "_count";
const std::string Translator::FILTER_RANGE_COUNT_NAME = "std::count";
const std::string Translator::FORALL_NAME = "_forall";
const std::string Translator::FORALL_RANGE_NAME = "std::all_of";
const std::string Translator::EXISTS_NAME = "_exists";
const std::string Translator::EXISTS_RANGE_NAME = "std::any_of";

// internal predefined functions for Matrix
const std::string Translator::TO_MATRIX_FUN_NAME = "_to_matrix";

// Precison Parameter
const double Translator::ZERO_EPS = 1e-30;

Translator::Translator() {
  useTag = false;
  prog = new code::Code();
  coreNs = new code::NamespaceDecl(MAIN_NAMESPACE_NAME);
  prog->addDecl(coreNs);
  coreCls = NULL;
  coreClsInit = NULL;
  coreClsConstructor = NULL;
  coreClsPrint = NULL;
  coreClsDebug = NULL;
  mainFun = NULL;
}

Translator::~Translator() {
  if (!useTag)
    delete prog;
}

void Translator::translate(std::shared_ptr<ir::BlogModel> model) {
  this->model = model;

  // Special Check for Matrix Usage
  if (model->isUseMatrix())
    prog->addOption("matrix");

  if (coreCls == NULL) {
    coreCls = code::ClassDecl::createClassDecl(coreNs, model->getName());
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

code::Code* Translator::getResult() {
  useTag = true;
  return prog;
}

code::FunctionDecl* Translator::transSampleAlg() {
  // for the moment, only supporting likelihood weighting algorithm
  // declare the sample method within coreCls
  SAMPLEFUN fun = DECLARE_SAMPLEFUN();
  fun->addStmt(
      new code::DeclStmt(
          new code::VarDecl(fun, WEIGHT_VAR_REF_NAME, DOUBLE_TYPE)));
  // declaring weight field in the class
  // ::: => vector<double> weight;
  code::FieldDecl::createFieldDecl(coreCls, GLOBAL_WEIGHT_VARNAME,
                                   DOUBLE_VECTOR_TYPE);
  // add initialization function in init()
  // :::=> weight.resize(LOCAL_NUM_SAMPLE_ARG_NAME);
  coreClsInit->addStmt(
      code::CallExpr::createMethodCall(
          GLOBAL_WEIGHT_VARNAME,
          VECTOR_RESIZE_METHOD_NAME,
          std::vector<code::Expr*>(
              { new code::Identifier(LOCAL_NUM_SAMPLE_ARG_NAME) })));
  //call the initialization function
  std::vector<code::Expr*> initArg;
  initArg.push_back(new code::Identifier(LOCAL_NUM_SAMPLE_ARG_NAME));
  fun->addStmt(
      new code::CallExpr(new code::Identifier(MAIN_INIT_FUN_NAME), initArg));
  // create for loop for the sampling
  // :::=> for (int cur_loop=0; cur_loop < number of sample; cur_loop++)
  code::Stmt* init = new code::BinaryOperator(
      new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME),
      new code::IntegerLiteral(INIT_SAMPLE_NUM + 1), code::OpKind::BO_ASSIGN);
  // ::: => cur_loop < n
  code::Expr* cond = new code::BinaryOperator(
      new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME),
      new code::Identifier(LOCAL_NUM_SAMPLE_ARG_NAME), code::OpKind::BO_LT);
  // ::: =>cur_loop++
  code::Expr* step = new code::BinaryOperator(
      new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME), NULL,
      code::OpKind::UO_INC);
  code::CompoundStmt* body = new code::CompoundStmt();
  // :::=> if (set_evidence(weight))
  //           evaluate_query(weight);
  code::CallExpr* set_evi = new code::CallExpr(
    new code::Identifier(SET_EVIDENCE_FUN_NAME),
    std::vector<code::Expr*>{new code::Identifier(WEIGHT_VAR_REF_NAME)});
  code::CallExpr* eval_q = new code::CallExpr(
    new code::Identifier(QUERY_EVALUATE_FUN_NAME),
    std::vector<code::Expr*>{new code::Identifier(WEIGHT_VAR_REF_NAME)});
  body->addStmt(new code::IfStmt(set_evi,eval_q));
  // :::==> weight[current_loop] = w;
  body->addStmt(
      new code::BinaryOperator(
          new code::ArraySubscriptExpr(
              new code::Identifier(GLOBAL_WEIGHT_VARNAME),
              new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME)),
          new code::Identifier(WEIGHT_VAR_REF_NAME), code::OpKind::BO_ASSIGN));
  fun->addStmt(new code::ForStmt(init, cond, step, body));
  return fun;
  //TODO adding other algorithms
}

void Translator::transTypeDomain(std::shared_ptr<ir::TypeDomain> td) {
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
      coreClsInit->addStmt(assignst);
    }
  }
  std::string numvar = getVarOfNumType(name);
  // create a field in the main class:::    int numvar;
  code::FieldDecl::createFieldDecl(coreCls, numvar, INT_TYPE);
  // create a field in the main class:::    int mark_numvar;
  std::string marknumvar = getMarkVarName(numvar);
  code::FieldDecl::createFieldDecl(coreCls, marknumvar, INT_TYPE);
  // add in the init function:::            numvar = len;
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::Identifier(numvar),
                               new code::IntegerLiteral((int) len),
                               code::OpKind::BO_ASSIGN));
  // add in the init function:::            mark_numvar = -1;
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::Identifier(marknumvar),
                               new code::IntegerLiteral(INIT_SAMPLE_NUM - 1),
                               code::OpKind::BO_ASSIGN));
  // create ensure_num function
  code::FunctionDecl* ensureFun = code::FunctionDecl::createFunctionDecl(
      coreCls, getEnsureFunName(numvar), VOID_TYPE, true);
  declared_funs[ensureFun->getName()] = ensureFun;
  // add in the init function to call this ensure_fun
  // :::=> ensure_numvar();
  coreClsInit->addStmt(
      new code::CallExpr(new code::Identifier(ensureFun->getName())));
  // create the function for getting number of objects in this instance, i.e.
  // numvar
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(
      coreCls, getGetterFunName(numvar), INT_TYPE, true);
  declared_funs[fun->getName()] = fun;

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
                           new code::Identifier(localnumvarname));
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
  fun->addStmt(
      new code::BinaryOperator(new code::Identifier(marknumvar),
                               new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME),
                               code::OpKind::BO_ASSIGN));
  fun->addStmt(new code::ReturnStmt(new code::Identifier(numvar)));
}

void Translator::transFun(std::shared_ptr<ir::FuncDefn> fd) {
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

code::FunctionDecl* Translator::transGetterFun(
    std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string getterfunname = getGetterFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());

  // __value__name for recording the value of the function application variable
  std::string valuevarname = getValueVarName(name);
  // adding in the main class a declaration of field for value of a random variable
  addFieldForFunVar(valuevarname, fd->getArgs(), valuetype);
  // __mark__name
  std::string markvarname = getMarkVarName(name);
  // adding in the main class a declaration of field for mark of a random variable
  addFieldForFunVar(markvarname, fd->getArgs());

  // Note: when adding field, refTag MUST be false!
  // Optimization for Vector/Map/Set Return
  if (valuetype.getName() == ARRAY_BASE_TYPE.getName()
    || valuetype.getName() == MAP_BASE_TYPE.getName()
    || valuetype.getName() == SET_BASE_TYPE.getName()
    || valuetype.getName() == MATRIX_TYPE.getName())
    valuetype.setRef(true);

  // define getter function :::==> __get_value()
  code::FunctionDecl* getterfun = code::FunctionDecl::createFunctionDecl(
      coreCls, getterfunname, valuetype);
  getterfun->setParams(transParamVarDecls(getterfun, fd->getArgs()));
  declared_funs[getterfun->getName()] = getterfun;
  code::Type valueRefType = valuetype;
  if (valuetype != BOOL_TYPE)  // special treatment for bool
    valueRefType.setRef(true);
  addFunValueRefStmt(getterfun, valuevarname, getterfun->getParams(),
                     VALUE_VAR_REF_NAME, valueRefType);
  addFunValueRefStmt(getterfun, markvarname, getterfun->getParams(),
                     MARK_VAR_REF_NAME);
  // now translating::: if (markvar == current sample num) then return value;
  code::Stmt* st = new code::IfStmt(
      new code::BinaryOperator(new code::Identifier(MARK_VAR_REF_NAME),
                               new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME),
                               code::OpKind::BO_EQU),
      new code::ReturnStmt(new code::Identifier(VALUE_VAR_REF_NAME)), NULL);
  getterfun->addStmt(st);
  // now should sample
  //now translate actual sampling part
  getterfun->addStmt(transClause(fd->getBody(), VALUE_VAR_REF_NAME));
  // now return the value
  // mark the variable first
  // ::: => markvar = cur_loop
  st = new code::BinaryOperator(
      new code::Identifier(MARK_VAR_REF_NAME),
      new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME),
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

code::FunctionDecl* Translator::transLikeliFun(
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
      coreCls, likelifunname, DOUBLE_TYPE);
  likelifun->setParams(transParamVarDecls(likelifun, fd->getArgs()));
  declared_funs[likelifun->getName()] = likelifun;
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

code::FunctionDecl* Translator::transSetterFun(
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
      coreCls, setterfunname, DOUBLE_TYPE);
  std::vector<code::ParamVarDecl*> args_with_value = transParamVarDecls(
      setterfun, fd->getArgs());
  declared_funs[setterfun->getName()] = setterfun;
  addFunValueAssignStmt(setterfun, valuevarname, args_with_value,
                        VALUE_ARG_NAME);
  addFunValueRefStmt(setterfun, markvarname, args_with_value,
                     MARK_VAR_REF_NAME);
  // set the argument of setter function
  args_with_value.push_back(
      new code::ParamVarDecl(setterfun, VALUE_ARG_NAME, valuetype));
  setterfun->setParams(args_with_value);
  code::Stmt* st = new code::BinaryOperator(
      new code::Identifier(MARK_VAR_REF_NAME),
      new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME),
      code::OpKind::BO_ASSIGN);
  setterfun->addStmt(st);
  // :::==> value_var = value_arg
  std::vector<code::Expr*> args_ref;
  for (auto a : fd->getArgs()) {
    args_ref.push_back(new code::Identifier(a->getVarName()));
  }
  st = new code::ReturnStmt(
      new code::CallExpr(new code::Identifier(likelifunname), args_ref));
  setterfun->addStmt(st);
  return setterfun;
}

void Translator::checkConstValue(std::shared_ptr<ir::FuncDefn> fd) {
  if (fd->isFixed() && fd->argSize() == 0 &&
    std::dynamic_pointer_cast<ir::Expr>(fd->getBody()) != nullptr) {
    constValTable.insert(getFixedFunName(fd->getName()));
  }
}

code::FunctionDecl* Translator::transFixedFun(
  std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string fixedfunname = getFixedFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());

  // special check to translate to const value instead of a function
  if (fd->argSize() == 0 && constValTable.count(fixedfunname) > 0) {
    code::FieldDecl::createFieldDecl(
      coreCls, fixedfunname, code::Type(fd->getRetTyp()->toString(),false,false,true),
      transExpr(std::dynamic_pointer_cast<ir::Expr>(fd->getBody())));
    return NULL;
  }

  // adding method declaration in the main class
  code::FunctionDecl* fixedfun = code::FunctionDecl::createFunctionDecl(
    coreCls, fixedfunname, valuetype);
  fixedfun->setParams(transParamVarDecls(fixedfun, fd->getArgs()));
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

code::Stmt* Translator::transClause(std::shared_ptr<ir::Clause> clause,
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
    if (retvar.size() > 0) {
      return new code::BinaryOperator(new code::Identifier(retvar),
                                      transExpr(expr, valuevar),
                                      code::OpKind::BO_ASSIGN);
    }
    else {
      return new code::ReturnStmt(transExpr(expr, valuevar));
    }
    // TODO no 100% correct here why??
  }
  //TODO: warning should not reach here
  return NULL;
}

code::ParamVarDecl* Translator::transParamVarDecl(
    code::DeclContext* context, const std::shared_ptr<ir::VarDecl> var) {
  return new code::ParamVarDecl(context, var->getVarName(),
                                mapIRTypeToCodeType(var->getTyp()));
}

std::vector<code::ParamVarDecl*> Translator::transParamVarDecls(
    code::DeclContext* context,
    const std::vector<std::shared_ptr<ir::VarDecl> > & vars) {
  std::vector<code::ParamVarDecl*> vds;
  for (auto v : vars) {
    vds.push_back(transParamVarDecl(context, v));
  }
  return vds;
}

code::Stmt* Translator::transMultiCaseBranch(std::shared_ptr<ir::Branch> br,
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
    code::FieldDecl::createFieldDecl(
      coreCls, mpName, code::Type(MAP_BASE_TYPE, std::vector<code::Type>({baseTy, INT_TYPE}),false,false,true),
      transMapExpr(mex));
  }
  auto iter = new code::CallExpr(
    new code::BinaryOperator(
      new code::Identifier(mpName),new code::Identifier("find"),code::OpKind::BO_FIELD),
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

code::Stmt* Translator::transBranch(std::shared_ptr<ir::Branch> br,
                                       std::string retvar,
                                       std::string valuevar) {
  if (br->getArgDim() > 1)
    return transMultiCaseBranch(br, retvar, valuevar); // Special Multi-Case Expr

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

code::Stmt* Translator::transIfThen(std::shared_ptr<ir::IfThen> ith,
                                       std::string retvar,
                                       std::string valuevar) {
  code::Expr* cond = transExpr(ith->getCond());
  code::Stmt* ifcl = transClause(ith->getThen(), retvar, valuevar);
  code::Stmt* elcl = NULL;
  if (ith->getElse())
    elcl = transClause(ith->getElse(), retvar, valuevar);
  return new code::IfStmt(cond, ifcl, elcl);
}

code::Expr* Translator::transExpr(std::shared_ptr<ir::Expr> expr,
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
    if (expr->getTyp() != NULL && expr->getTyp()->getTyp() == ir::IRConstant::MATRIX) {
      // cannot use EQU. Instead, we need to apply norm here
      auto diff = new code::BinaryOperator(new code::Identifier(valuevar), res, code::OpKind::BO_MINUS);
      auto mat_norm = new code::CallExpr(new code::Identifier("norm"), std::vector<code::Expr*>{diff});
      res = new code::BinaryOperator(mat_norm, new code::FloatingLiteral(ZERO_EPS), code::OpKind::BO_LEQ);
    }
    else
      res = new code::BinaryOperator(new code::Identifier(valuevar), res, code::OpKind::BO_EQU);
  }

  // TODO translate other expression
  // if valuevar is provided it should be
  if (!used)
    for (auto ag : args)
      delete ag;
  return res;
}

code::Expr* Translator::transOriginRefer(
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

code::Expr* Translator::transCardExpr(std::shared_ptr<ir::CardExpr> cardexp,
                                         std::string valuevar) {
  std::shared_ptr<ir::CondSet> setexp = std::dynamic_pointer_cast<ir::CondSet>(
      cardexp->getBody());
  assert(setexp != nullptr);
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

code::Expr* Translator::transSetExpr(std::shared_ptr<ir::SetExpr> e) {
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

  if (condset->getCond() != nullptr) {
    auto func = new code::LambdaExpr(code::LambdaKind::REF, BOOL_TYPE);
    func->addParam(
      new code::ParamVarDecl(func, condset->getVar()->getVarName(), INT_TYPE));
    func->addStmt(new code::ReturnStmt(transExpr(condset->getCond())));
    args.push_back(func);
  }

  if (condset->getFunc() != nullptr) { // applied function associated
    auto func = new code::LambdaExpr(code::LambdaKind::REF, mapIRTypeToCodeType(condset->getFunc()->getTyp()));
    func->addParam(
      new code::ParamVarDecl(func, condset->getVar()->getVarName(), INT_TYPE));
    func->addStmt(new code::ReturnStmt(transExpr(condset->getFunc())));
    args.push_back(func);

    // call builtin function: _apply<...>(...)
    // Note: currently we only support NameTy!
    return new code::CallExpr(
      new code::TemplateExpr(
        new code::Identifier(APPLY_FUNC_NAME),
        std::vector<code::Expr*>{ new code::Identifier(mapIRTypeToCodeType(condset->getFunc()->getTyp()).getName()) }),
      args);
  }
  else { // no applied function, pure condition set
    if (condset->getCond() == nullptr) { // no condition here
      // _gen_full(n)
      return new code::CallExpr(new code::Identifier(GEN_FULL_SET_NAME), args);
    }
    else { // with condition
      // _filter(n, cond)
      return new code::CallExpr(new code::Identifier(FILTER_FUNC_NAME), args);
    }
  }
}

/*
 *  Note: Translation Sample 
 *    Input: forall A a : cond(a)
 *    Output:
 *        _forall(__get_num_A(), [&](int a)->bool{return cond(a);})
 */
code::Expr* Translator::transQuantForm(std::shared_ptr<ir::QuantForm> qt, code::Expr* cond) {
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

code::Expr* Translator::transMapExpr(std::shared_ptr<ir::MapExpr> mex) {
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

code::Expr* Translator::transOprExpr(std::shared_ptr<ir::OprExpr> opr,
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

code::Expr* Translator::transArrayExpr(std::shared_ptr<ir::ArrayExpr> opr,
  std::vector<code::Expr*> args) {
  std::vector<code::Expr*> sub{ new code::ListInitExpr(args) };
  return new code::CallClassConstructor(mapIRTypeToCodeType(opr->getTyp()),sub);
}

code::Expr* Translator::transMatrixExpr(std::shared_ptr<ir::MatrixExpr> mat) {
  /*
    Construction of Matrix
    1. construct a row vector
    2. construct a col vector
    3. construct a fixed 2-D real matrix
    4. construct a general 2-D real matrix
  */
  std::vector<code::Expr*> args;
  if (mat->isColVec() || mat->isRowVec()) { // row vector / col vector, which could be constructed via vector directly
    for (size_t i = 0; i < mat->argSize(); ++ i)
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

code::Expr* Translator::transDistribution(
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
        code::FieldDecl::createFieldDecl(
            coreCls, distvarname, code::Type(UNIFORM_INT_DISTRIBUTION_NAME));
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
        code::FieldDecl::createFieldDecl(
            coreCls, distvarname, code::Type(UNIFORM_CHOICE_DISTRIBUTION_NAME));
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
      code::FieldDecl::createFieldDecl(coreCls, distvarname, code::Type(name));
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
      code::FieldDecl::createFieldDecl(coreCls, distvarname, code::Type(name));
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

void Translator::createInit() {
  // adding setup for
  // 1. member declarations for core class, need valuearray, mark array, ...
  // 2. initialization function to initialize the values (function called in sample(n)
  // 3. print method
  // 4. debug method
  coreClsConstructor = code::ClassConstructor::createClassConstructor(coreCls);
  coreClsInit = code::FunctionDecl::createFunctionDecl(coreCls,
                                                       MAIN_INIT_FUN_NAME,
                                                       VOID_TYPE);

  // add method print() in main class to print the answers
  coreClsPrint = code::FunctionDecl::createFunctionDecl(
      coreCls, ANSWER_PRINT_METHOD_NAME, VOID_TYPE);

  // add method debug() in main class to print the current state of the possible world
  // TODO add a flag to support debug or not
  coreClsDebug = code::FunctionDecl::createFunctionDecl(coreCls,
                                                        MAIN_DEBUG_METHOD_NAME,
                                                        VOID_TYPE);

  std::vector<code::ParamVarDecl*> args;
  args.push_back(
      new code::ParamVarDecl(coreClsInit, LOCAL_NUM_SAMPLE_ARG_NAME, INT_TYPE));
  coreClsInit->setParams(args);
  code::FieldDecl::createFieldDecl(coreCls, CURRENT_SAMPLE_NUM_VARNAME,
                                   INT_TYPE);
  code::FieldDecl::createFieldDecl(coreCls, RANDOM_DEVICE_VAR_NAME,
                                   RANDOM_ENGINE_TYPE);
}

// add the in the class a field variable for a funcappvar with params
void Translator::addFieldForFunVar(
    std::string varname,
    const std::vector<std::shared_ptr<ir::VarDecl> >& params,
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
      ensureFun->addStmt(code::CallExpr::createMethodCall(
          varname, DYNAMICTABLE_RESIZE_METHOD_NAME,
          std::vector<code::Expr*>(
              {new code::IntegerLiteral((int)id),
               new code::Identifier(numvarname_for_arg)})));
    }
  }
  // adding in the main class a declaration of field for value of a random
  // variable
  code::FieldDecl::createFieldDecl(coreCls, varname, valueType);
}

void Translator::addFunValueRefStmt(
    code::FunctionDecl* fun, std::string valuevarname,
    const std::vector<code::ParamVarDecl*>& valueindex, std::string valuerefname,
    code::Type varType) {
  // the value of this function application variable is stored in
  // valuevarname[index1][index2]...
  // where the index are corresponding to the arguments
  code::Expr* exp = new code::Identifier(valuevarname);
  for (auto prm : valueindex) {
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

void Translator::addFunValueAssignStmt(
    code::FunctionDecl* fun, std::string valuevarname,
    std::vector<code::ParamVarDecl*>& valueindex, std::string valuerefname) {
  // the value of this function application variable is stored in
  // valuevarname[index1][index2]...
  // where the index are corresponding to the arguments
  code::Expr* exp = new code::Identifier(valuevarname);
  for (auto prm : valueindex) {
    exp = new code::ArraySubscriptExpr(exp, new code::Identifier(prm->getId()));
  }
  // assign valuerefname to the function application variable value to
  code::Stmt* dst = new code::BinaryOperator(exp,
                                             new code::Identifier(valuerefname),
                                             code::OpKind::BO_ASSIGN);
  fun->addStmt(dst);
}

void Translator::transEvidence(code::FunctionDecl* fun,
                                  std::shared_ptr<ir::Evidence> evid, bool transFuncApp) {
  const std::shared_ptr<ir::Expr>& left = evid->getLeft();
  // check whether left is a function application variable
  std::shared_ptr<ir::FunctionCall> leftexp = std::dynamic_pointer_cast<
      ir::FunctionCall>(left);
  if (leftexp && transFuncApp) {
    // left side of the evidence is a function application
    std::string blogfunname = leftexp->getRefer()->getName();  // the function name in blog model
    std::string setterfunname = getSetterFunName(blogfunname);  // setter function for the blog function predicate
    std::vector<code::Expr*> args;
    // now translate arguments to this setter function
    for (auto a : leftexp->getArgs()) {
      args.push_back(transExpr(a));
    }
    // assign the right side of the evidence to left function application variable
    args.push_back(transExpr(evid->getRight()));
    // call setter function and calculate likelihood
    // :::=> weight += set_evidence();
    code::Stmt* st = new code::BinaryOperator(
        new code::Identifier(WEIGHT_VAR_REF_NAME),
        new code::CallExpr(new code::Identifier(setterfunname), args),
        COMPUTE_LIKELIHOOD_IN_LOG ?
            code::OpKind::BO_SPLUS : code::OpKind::BO_SMUL);
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
    //st = new code::IfStmt(cond, st);
    fun->addStmt(st);
    return;
  }

  // check whether left is a cardinality expression
  std::shared_ptr<ir::CardExpr> cardexp =
      std::dynamic_pointer_cast<ir::CardExpr>(left);

  // TODO: remove transFuncApp
  //    Now we have to firstly print all rejection sampling stmts
  //    Then print the likelihood weighing stmts
  //    TransFuncApp is a switch for this
  if (cardexp && !transFuncApp) {
    // translate cardinality evidence
    // check whether the evidence doesnot hold
    code::Expr* cond = new code::BinaryOperator(transCardExpr(cardexp),
                                                transExpr(evid->getRight()),
                                                code::OpKind::BO_NEQ);
    code::Stmt* st = new code::ReturnStmt(new code::BooleanLiteral(false));
    st = new code::IfStmt(cond, st);
    fun->addStmt(st);
    return;
  }
  // TODO adding support for other evidence
  // 1. better setting evidence for Cardinality evidence
}

void Translator::transAllEvidence(
    std::vector<std::shared_ptr<ir::Evidence> > evids) {
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(
      coreCls, SET_EVIDENCE_FUN_NAME, BOOL_TYPE);
  fun->setParams(std::vector<code::ParamVarDecl*>{new code::ParamVarDecl(fun, WEIGHT_VAR_REF_NAME, DOUBLE_REF_TYPE)});

  fun->addStmt(new code::BinaryOperator(
    new code::Identifier(WEIGHT_VAR_REF_NAME),
    new code::FloatingLiteral(COMPUTE_LIKELIHOOD_IN_LOG ? 0 : 1.0), code::OpKind::BO_ASSIGN));

  for (auto evid : evids) {
    // Firstly Translate all rejection sampling stmts
    transEvidence(fun, evid, false);
  }
  
  for (auto evid : evids) {
    // Firstly Translate all likelihood weighing stmts
    transEvidence(fun, evid, true);
  }
  fun->addStmt(new code::ReturnStmt(new code::BooleanLiteral(true)));
}

void Translator::transAllQuery(
    std::vector<std::shared_ptr<ir::Query> > queries) {
  // create evaluate function
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(
      coreCls, QUERY_EVALUATE_FUN_NAME, VOID_TYPE, true);
  // setting arguments for queryfun
  std::vector<code::ParamVarDecl*> args;
  // query function has one argument of double, for weight
  args.push_back(new code::ParamVarDecl(fun, WEIGHT_VAR_REF_NAME, DOUBLE_TYPE));
  fun->setParams(args);
  int index = 0;
  for (auto qr : queries) {
    transQuery(fun, qr, index);
    ++index;
  }
}

void Translator::transQuery(code::FunctionDecl* fun,
                               std::shared_ptr<ir::Query> qr, int n) {
  // Register Printing Hist Class
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
  code::FieldDecl::createFieldDecl(
      coreCls, answervarname,
      code::Type(HISTOGRAM_CLASS_NAME, std::vector<code::Type>( {
          mapIRTypeToCodeType(qr->getVar()->getTyp()) })),
      initvalue);
  std::vector<code::Expr*> args;
  args.push_back(transExpr(qr->getVar()));
  args.push_back(new code::Identifier(WEIGHT_VAR_REF_NAME));
  fun->addStmt(
      code::CallExpr::createMethodCall(answervarname, HISTOGRAM_ADD_METHOD_NAME,
                                       args));
  // add print this result in print()
  // :::=> answer_id.print("query expr");
  coreClsPrint->addStmt(
      code::CallExpr::createMethodCall(answervarname,
                                       HISTOGRAM_PRINT_METHOD_NAME,
                                       std::vector<code::Expr*> { new code::StringLiteral(qr->str()) }));
}

code::Type Translator::mapIRTypeToCodeType(const ir::Ty* ty, bool isRef, bool isPtr) {
  // TODO add support for more ref type
  // TODO: To Make the type more general for other language, i.e. Java!
  ///    Note: in IR, the type->toString() will return the corresponding C++ translation of that type
  switch (ty->getTyp()) {
    case ir::IRConstant::BOOL:
      return code::Type(CHAR_TYPE.getName(), isRef, isPtr); // Special Treatment for Bool in C++
    case ir::IRConstant::INT:
    case ir::IRConstant::DOUBLE:
    case ir::IRConstant::STRING:
    case ir::IRConstant::TIMESTEP:
    case ir::IRConstant::MATRIX:
      return code::Type(ty->toString(), isRef, isPtr);
    case ir::IRConstant::ARRAY: {
      auto arr = dynamic_cast<const ir::ArrayTy*>(ty);
      std::vector<code::Type> args;
      args.push_back(mapIRTypeToCodeType(arr->getBase(), false));
      return code::Type(ARRAY_BASE_TYPE.getName(), args, isRef, isPtr);
    }
    case ir::IRConstant::SET: {
      auto st = dynamic_cast<const ir::SetTy*>(ty);
      std::vector<code::Type> args;
      args.push_back(mapIRTypeToCodeType(st->getRefer(), false));
      return code::Type(SET_BASE_TYPE.getName(), args, isRef, isPtr);
    }
    case ir::IRConstant::MAP: {
      auto mp = dynamic_cast<const ir::MapTy*>(ty);
      std::vector<code::Type> args;
      args.push_back(mapIRTypeToCodeType(mp->getFrom(), false));
      args.push_back(mapIRTypeToCodeType(mp->getTo(), false));
      return code::Type(MAP_BASE_TYPE.getName(), args, isRef, isPtr);
    }
    default:
      return isRef ? INT_REF_TYPE : INT_TYPE;  // all declared type return int type
      // assume isPtr = false
  }
}

code::Expr* Translator::transConstSymbol(
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

code::Expr* Translator::transFunctionCall(
    std::shared_ptr<ir::FunctionCall> fc, std::vector<code::Expr*> args) {
  std::string getterfunname;
  // Special Check for builtin functions
  if (fc->isBuiltin()) {
    // Special Check for vstack and hstack
    if (dynamic_cast<const predecl::MatrixStackFuncDecl*>(fc->getBuiltinRefer()) != NULL) {
      auto lst = new code::ListInitExpr(args);
      return new code::CallExpr(new code::Identifier(fc->getBuiltinRefer()->getName()), std::vector<code::Expr*>{lst});
    }
    // Special Check for aggregate function
    if (dynamic_cast<const predecl::SetAggrFuncDecl*>(fc->getBuiltinRefer()) != NULL) {
      auto setexpr = std::dynamic_pointer_cast<ir::CondSet>(fc->get(0));
      if (setexpr != nullptr && args.size() == 1 && setexpr->getFunc() != nullptr) {
        // assert(args.size() == 1);
        // assert(args[0].size() == 2 + (setexpr->getCond() != nullptr));
        auto set_gen = args[0];
        args = set_gen->getArgs();
        set_gen->clearArgs();
        delete set_gen;
      }
      args.push_back(
        new code::TemplateExpr(
          new code::Identifier(fc->getBuiltinRefer()->getName()),
          std::vector<code::Expr*>{new code::Identifier(mapIRTypeToCodeType(fc->getTyp()).getName())}));
      return new code::CallExpr(
        new code::TemplateExpr(
          new code::Identifier(AGGREGATE_FUNC_NAME),
          std::vector<code::Expr*>{new code::Identifier(mapIRTypeToCodeType(fc->getTyp()).getName())}),
        args);
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

void Translator::createMain() {
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

  st = new code::DeclStmt(
      new code::VarDecl(
          mainFun, SAMPLER_VAR_NAME, code::Type(std::vector<std::string>( {
              coreNs->getName() }),
                                                coreCls->getName())));
  mainFun->addStmt(st);
  std::vector<code::Expr*> args;
  args.push_back(new code::IntegerLiteral(TOTAL_NUM_SAMPLES));
  st = code::CallExpr::createMethodCall(SAMPLER_VAR_NAME,
                                        MAIN_SAMPLING_FUN_NAME, args);
  mainFun->addStmt(st);
  st = code::CallExpr::createMethodCall(SAMPLER_VAR_NAME,
                                        ANSWER_PRINT_METHOD_NAME);
  mainFun->addStmt(st);

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

inline TYPEDEFN Translator::DECLARE_TYPE(std::string name) {
  // create a class for this declared type
  TYPEDEFN cd = code::ClassDecl::createClassDecl(coreNs, name);
  code::FieldDecl::createFieldDecl(cd, DISTINCT_FIELDNAME, STRING_TYPE);
  // declare a vector to hold all instance in this type
  std::string inst_var_name = getInstanceArrayName(name);
  code::FieldDecl::createFieldDecl(
      coreCls,
      inst_var_name,
      code::Type(VECTOR_CLASS_NAME,
                 std::vector<code::Type>( { code::Type(name) })));
  return cd;
}

inline ORIGINDEFN Translator::DECLARE_ORIGIN_FIELD(TYPEDEFN typedf,
                                                      std::string originname,
                                                      TYPE origintype) {
  return code::FieldDecl::createFieldDecl(typedf, originname, origintype);
}

inline STMT Translator::CREATE_INSTANCE(std::string tyname,
                                           std::string instname,
                                           std::vector<EXPR> originvalues,
                                           EXPR ncopy) {
  // this is the holder for the instances
  std::string inst_var_name = getInstanceArrayName(tyname);
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
  
inline EXPR Translator::ACCESS_ORIGIN_FIELD(std::string tyname,
                                               std::string originname,
                                               EXPR originarg) {
  // this is the holder for the instances
  std::string inst_var_name = getInstanceArrayName(tyname);
  EXPR exp = new code::ArraySubscriptExpr(new code::Identifier(inst_var_name), originarg);
  exp = new code::BinaryOperator(exp, new code::Identifier(originname), code::OpKind::BO_FIELD);
  return exp;
}

inline SAMPLEFUN Translator::DECLARE_SAMPLEFUN() {
  // declare the sample method within coreCls
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(
      coreCls, MAIN_SAMPLING_FUN_NAME, VOID_TYPE);
  std::vector<code::ParamVarDecl*> args;
  args.push_back(
      new code::ParamVarDecl(fun, LOCAL_NUM_SAMPLE_ARG_NAME, INT_TYPE));
  fun->setParams(args);
  return fun;
}

} /* namespace codegen */
} /* namespace swift */

