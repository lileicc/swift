/*
 * MHTranslator.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: yiwu
 */

#include <cassert>
#include <iostream>
#include "../predecl/PreDecl.h"
#include "../predecl/MatrixStackFuncDecl.h"
#include "../predecl/SetAggrFuncDecl.h"


#include "MHTranslator.h"

namespace swift {
namespace codegen {

const std::string MHTranslator::CoreQueryFuncName = "_eval_query";
const std::string MHTranslator::CoreStorageInitFuncName = "_init_storage";
const std::string MHTranslator::CoreWorldInitFuncName = "_init_world";
const std::string MHTranslator::CoreGarbageCollectFuncName = "_garbage_collection";
const std::string MHTranslator::CorePrintFuncName = "_print_answer";
const std::string MHTranslator::MCMCResampleFuncName = "mcmc_sample_single_iter"; // this function is from MCMC.h

// Global Class/Var Name
const std::string MHTranslator::BayesVarClsName = "BayesVar";
const std::string MHTranslator::ActiveListName = "_active_list";
const std::string MHTranslator::RoundCounterVarName = "_tot_round";
const std::string MHTranslator::TotalRoundVarName = "_TOT_LOOP";
const std::string MHTranslator::BurnInVarName = "_BURN_IN";

// BayesVar Method Name
const std::string MHTranslator::MCMC_Global_MHAlgo_MethodName = "mh_parent_resample_arg";
const std::string MHTranslator::MCMC_Global_MHAlgo_SymProp_MethodName = "mh_symmetric_resample_arg";
const std::string MHTranslator::MCMC_Global_MHNumVarAlgo_MethodName = "mh_parent_resample_numvar_arg";
const std::string MHTranslator::MCMC_Global_Clear_MethodName = "clear_arg";
const std::string MHTranslator::MCMC_Global_GetVal_MethodName = "getval_arg";
const std::string MHTranslator::MCMC_Global_GetCache_MethodName = "getcache_arg";
const std::string MHTranslator::MCMC_Global_EnsureCache_MethodName = "ensure_cache";
const std::string MHTranslator::MCMC_Global_GetValNumVar_MethodName = "getval_numvar_arg";
const std::string MHTranslator::MCMC_Global_GetCacheNumVar_MethodName = "getcache_numvar_arg";
const std::string MHTranslator::MCMC_Global_AddChild_MethodName = "add_child";
const std::string MHTranslator::MCMC_Global_RemoveChild_MethodName = "erase_child";
const std::string MHTranslator::MCMC_Global_AddContig_MethodName = "add_contig";
const std::string MHTranslator::MCMC_Global_RemoveContig_MethodName = "erase_contig";
const std::string MHTranslator::MCMC_GetName_MethodName = "getname";
const std::string MHTranslator::MCMC_Resample_MethodName = "mcmc_resample";
const std::string MHTranslator::MCMC_Clear_MethodName = "clear";
const std::string MHTranslator::MCMC_GetVal_MethodName = "getval";
const std::string MHTranslator::MCMC_GetCache_MethodName = "getcache";
const std::string MHTranslator::MCMC_SampleVal_MethodName = "sample";
const std::string MHTranslator::MCMC_SampleCache_MethodName = "sample_cache";
const std::string MHTranslator::MCMC_GetLike_MethodName = "getlikeli";
const std::string MHTranslator::MCMC_GetCacheLike_MethodName = "getcachelikeli";
const std::string MHTranslator::MCMC_ActiveEdge_MethodName = "active_edge";
const std::string MHTranslator::MCMC_RemoveEdge_MethodName = "remove_edge";
//   ==> Evidence Related
const std::string MHTranslator::MCMC_CheckObs_MethodName = "check_obs";
const std::string MHTranslator::MCMC_UpdateObs_MethodName = "update_obs";
//   ==> Number Variable Related
const std::string MHTranslator::MCMC_GetPropSize_MethodName = "get_property_size";
const std::string MHTranslator::MCMC_UpdateRef_MethodName = "update_reference";
const std::string MHTranslator::MCMC_ClearRef_MethodName = "clear_reference";
const std::string MHTranslator::MCMC_CalcRefDiff_MethodName = "get_reference_diff";
const std::string MHTranslator::MCMC_EnsureSize_MethodName = "ensure_size";
const std::string MHTranslator::MCMC_EnsureSupport_MethodName = "ensure_support_prop_arg";
const std::string MHTranslator::MCMC_EnsureCache_MethodName = "ensure_cache_prop_arg";
const std::string MHTranslator::MCMC_ClearProp_MethodName = "clear_prop_arg";

// BayesVar member variable
const std::string MHTranslator::MCMC_Val_VarName = "val";
const std::string MHTranslator::MCMC_Cache_VarName = "cache_val";
const std::string MHTranslator::MCMC_CachedFlag_VarName = "is_cached";
const std::string MHTranslator::MCMC_ActiveFlag_VarName = "is_active";
const std::string MHTranslator::MCMC_ObsFlag_VarName = "is_obs";
// ==> Number Variable Related
const std::string MHTranslator::MCMC_Capacity_VarName = "capacity";

// Temp variable
const std::string MHTranslator::TEMP_N_NAME = "_n";
const std::string MHTranslator::TEMP_FROM_NAME = "_from";
const std::string MHTranslator::TEMP_TO_NAME = "_to";
const std::string MHTranslator::TEMP_IND_NAME = "_i";
const std::string MHTranslator::TEMP_VAL_NAME = "_t_val";
const std::string MHTranslator::TEMP_FLAG_NAME = "_t_flag";
const std::string MHTranslator::TEMP_LOOP_VAR_NAME = "_j";

// Util Func Name
const std::string MHTranslator::UtilSetEviFuncName = "_util_set_evidence";
const std::string MHTranslator::UtilUpdateRefFuncName = "_util_update_reference";
const std::string MHTranslator::UtilUpdateObsFuncName = "_util_update_evidence";
const std::string MHTranslator::UtilClearRefFuncName = "_util_clear_reference";
const std::string MHTranslator::UtilCalcRefDiffFuncName = "_util_calc_reference_diff";
const std::string MHTranslator::UtilFreeObjFuncName = "_free_obj";

// Util MCMC Proposal Distrib Name
const std::string MHTranslator::UtilPropUniGaussName = "_gaussian_prop";
const std::string MHTranslator::UtilPropMultiGaussName = "_multigaussian_prop";

// Types
const code::Type MHTranslator::NumberVar_Base_Type = code::Type("NumberVar");

///////////////////////////////////////////////////////////////
//  Util Functions for Metropolis-Hastings
///////////////////////////////////////////////////////////////
std::string MHTranslator::getNameOfNumberVar(std::string name) {
  return "_NumVar_"+name;
}

std::string MHTranslator::getStoreOfNumberVar(std::string name) {
  return "_mem_" + name + "_Num";
}

std::string MHTranslator::getNameOfRandomVar(std::string name) {
  return "_Var_" + name;
}

std::string MHTranslator::getStoreOfRandomVar(std::string name) {
  return "_mem_" + name;
}

code::Expr* MHTranslator::createPtrMethodCall(code::Expr* ptr, std::string method_name, std::vector<code::Expr*> args) {
  code::Expr* ret = new code::BinaryOperator(ptr, new code::Identifier(method_name), code::OpKind::BO_POINTER);
  ret = new code::CallExpr(ret, args);
  return ret;
}

code::Expr* MHTranslator::createRandomVarRef(std::shared_ptr<ir::Expr> expr) {
  // TODO: to handle more general expressions referring to a random variable

  // random function
  auto fun = std::dynamic_pointer_cast<ir::FunctionCall>(expr);
  if (fun != nullptr) {
    if (fun->getKind() != ir::IRConstant::RANDOM) return NULL;
    std::vector<code::Expr*> args;
    for (auto&a : fun->getArgs()) {
      args.push_back(transExpr(a));
    }
    return transFunctionCall(fun, args, false);
  }

  // number variable
  auto num = std::dynamic_pointer_cast<ir::CardExpr>(expr);
  if (num != nullptr) {
    auto st = std::dynamic_pointer_cast<ir::CondSet>(num->getBody());
    if (st == nullptr) return NULL;
    if (st->getCond() != nullptr) return NULL; // cannot handle condition set now

    return transCardExpr(num, "", false);
  }

  return NULL;
}

std::string MHTranslator::getRandomVarRefName(std::shared_ptr<ir::Expr> expr) {
  // TODO: to handle more general expressions referring to a random variable

  // random function
  auto fun = std::dynamic_pointer_cast<ir::FunctionCall>(expr);
  if (fun != nullptr) {
    if (fun->getKind() != ir::IRConstant::RANDOM) return "";
    return fun->getRefer()->getName();
  }

  // number variable
  auto num = std::dynamic_pointer_cast<ir::CardExpr>(expr);
  if (num != nullptr) {
    auto st = std::dynamic_pointer_cast<ir::CondSet>(num->getBody());
    if (st == nullptr) return "";
    if (st->getCond() != nullptr) return ""; // cannot handle condition set now
    auto ty = dynamic_cast<const ir::NameTy*>(st->getVar()->getTyp());
    if (ty == NULL) return "";
    return ty->getRefer()->getName();
  }

  return NULL;
}

void MHTranslator::addDefualtMethods(std::string name, code::ClassDecl* clsdef, code::Type clsValRefType, bool isNumberVar) {
  code::FunctionDecl* f_ptr;

  // add default methods
  auto& mp = varMethods[name]; // NOTE: should be Referenced!
  // string getname(){};
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_GetName_MethodName, STRING_TYPE);
  if (isNumberVar)
    f_ptr->addStmt(new code::ReturnStmt(new code::StringLiteral("#" + name)));
  else {
    // TODO: To fill getname() in the general case later
    f_ptr->addStmt(new code::ReturnStmt(new code::StringLiteral(name)));
  }
  mp[MCMC_GetName_MethodName] = f_ptr;
  // T& getval() = {return getval_arg(this);}
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_GetVal_MethodName, clsValRefType);
  f_ptr->addStmt(new code::ReturnStmt(
    new code::CallExpr(
      new code::Identifier(isNumberVar ? MCMC_Global_GetValNumVar_MethodName : MCMC_Global_GetVal_MethodName),
      std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)})));
  mp[MCMC_GetVal_MethodName] = f_ptr;
  // T& getcache() = {return getval_arg(this);}
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_GetCache_MethodName, clsValRefType);
  f_ptr->addStmt(new code::ReturnStmt(
    new code::CallExpr(
    new code::Identifier(isNumberVar ? MCMC_Global_GetCacheNumVar_MethodName : MCMC_Global_GetCache_MethodName),
    std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)})));
  mp[MCMC_GetCache_MethodName] = f_ptr;
  // void clear() { clear_arg(this); }
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_Clear_MethodName, VOID_TYPE);
  f_ptr->addStmt(new code::ReturnStmt(
    new code::CallExpr(
    new code::Identifier(MCMC_Global_Clear_MethodName),
    std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)})));
  mp[MCMC_Clear_MethodName] = f_ptr;
  // double getlikeli()
  //    --> filled later
  mp[MCMC_GetLike_MethodName] = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_GetLike_MethodName, DOUBLE_TYPE);
  // double getcachelikeli()
  //    --> filled later
  mp[MCMC_GetCacheLike_MethodName] = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_GetCacheLike_MethodName, DOUBLE_TYPE);
  // void sample()
  //    --> filled later
  mp[MCMC_SampleVal_MethodName] = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_SampleVal_MethodName, VOID_TYPE);
  // void sample_cache()
  //    --> filled later
  mp[MCMC_SampleCache_MethodName] = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_SampleCache_MethodName, VOID_TYPE);
  // void active_edge()
  //    --> filled later
  mp[MCMC_ActiveEdge_MethodName] = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_ActiveEdge_MethodName, VOID_TYPE);
  // void remove_edge()
  //    --> filled later
  mp[MCMC_RemoveEdge_MethodName] = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_RemoveEdge_MethodName, VOID_TYPE);
  // void mcmc_resample()
  //    --> Special Treatment!
  mp[MCMC_Resample_MethodName] = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_Resample_MethodName, VOID_TYPE);
}

void MHTranslator::addEvidenceCheckSpecialMethods(std::string name, code::ClassDecl* clsdef) {
  code::FunctionDecl* f_ptr;

  // add evidence checking related methods
  auto& mp = varMethods[name]; // NOTE: should be Referenced!

  // bool check_obs();
  if (mp.count(MCMC_CheckObs_MethodName) > 0) return ; // already registered!
  mp[MCMC_CheckObs_MethodName] = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_CheckObs_MethodName, BOOL_TYPE);
  // void update_obs(bool flag);
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_UpdateObs_MethodName, VOID_TYPE);
  f_ptr->setParams(std::vector<code::ParamVarDecl*> { new code::ParamVarDecl(f_ptr, TEMP_FLAG_NAME, BOOL_TYPE)});
  mp[MCMC_UpdateObs_MethodName] = f_ptr;
}

void MHTranslator::addNumberVarSpecialMethods(std::string name, code::ClassDecl* clsdef, int prop_size) {
  code::FunctionDecl* f_ptr;

  // Number Variable Related special functions
  auto& mp = varMethods[name]; // NOTE: should be Referenced!
  // inline int get_property_size() {return prop_size;}
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_GetPropSize_MethodName, INT_TYPE, true);
  f_ptr->addStmt(new code::ReturnStmt(new code::IntegerLiteral(prop_size)));
  mp[MCMC_GetPropSize_MethodName] = f_ptr;

  // ===> All the following will be filled later!
  // ensure_size(int n);
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_EnsureSize_MethodName, VOID_TYPE);
  f_ptr->setParams(std::vector<code::ParamVarDecl*>{new code::ParamVarDecl(f_ptr, TEMP_N_NAME, INT_TYPE)});
  mp[MCMC_EnsureSize_MethodName] = f_ptr;
  // clear_prop_arg(int i);
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_ClearProp_MethodName, VOID_TYPE);
  f_ptr->setParams(std::vector<code::ParamVarDecl*>{new code::ParamVarDecl(f_ptr, TEMP_IND_NAME, INT_TYPE)});
  mp[MCMC_ClearProp_MethodName] = f_ptr;
  // ensure_support_prop_arg(int i);
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_EnsureSupport_MethodName, VOID_TYPE);
  f_ptr->setParams(std::vector<code::ParamVarDecl*>{new code::ParamVarDecl(f_ptr, TEMP_IND_NAME, INT_TYPE)});
  mp[MCMC_EnsureSupport_MethodName] = f_ptr;
  // ensure_support_prop_arg(int i);
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_EnsureCache_MethodName, VOID_TYPE);
  f_ptr->setParams(std::vector<code::ParamVarDecl*>{new code::ParamVarDecl(f_ptr, TEMP_IND_NAME, INT_TYPE)});
  mp[MCMC_EnsureCache_MethodName] = f_ptr;
}

void MHTranslator::addObjectRefSpecialMethods(std::string name, std::string objTypeName, code::ClassDecl* clsdef) {
  void clear_reference();
  void update_reference();
  int get_reference_diff(int from, int to);

  code::FunctionDecl* f_ptr;

  // Object Reference Variable Related special functions
  auto& mp = varMethods[name]; // NOTE: should be Referenced!

  // clear_reference() {_util_clear_reference(NumVar, this, val);}
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_ClearRef_MethodName, VOID_TYPE);
  f_ptr->addStmt(new code::CallExpr(
    new code::Identifier(UtilClearRefFuncName),
    std::vector<code::Expr*>{
        new code::Identifier(getStoreOfNumberVar(objTypeName)),
        new code::Identifier(KEYWORD_THIS),
        new code::Identifier(MCMC_Val_VarName)
    }));
  mp[MCMC_ClearRef_MethodName] = f_ptr;

  // update_reference() {_util_update_reference(NumVar, this, val);}
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_UpdateRef_MethodName, VOID_TYPE);
  f_ptr->addStmt(new code::CallExpr(
    new code::Identifier(UtilUpdateRefFuncName),
    std::vector<code::Expr*>{
      new code::Identifier(getStoreOfNumberVar(objTypeName)),
      new code::Identifier(KEYWORD_THIS),
      new code::Identifier(MCMC_Val_VarName)
    }));
  mp[MCMC_UpdateRef_MethodName] = f_ptr;

  // int get_reference_diff(int from, int to) {return _util_calc_reference_diff(NumVar, from, to);}
  f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_CalcRefDiff_MethodName, INT_TYPE);
  f_ptr->setParams(std::vector<code::ParamVarDecl*>{
      new code::ParamVarDecl(f_ptr, TEMP_FROM_NAME,INT_TYPE),
      new code::ParamVarDecl(f_ptr, TEMP_TO_NAME,INT_TYPE)});
  f_ptr->addStmt(new code::ReturnStmt(new code::CallExpr(
    new code::Identifier(UtilCalcRefDiffFuncName),
    std::vector<code::Expr*>{
      new code::Identifier(getStoreOfNumberVar(objTypeName)),
      new code::Identifier(TEMP_FROM_NAME),
      new code::Identifier(TEMP_TO_NAME)
    })));
  mp[MCMC_CalcRefDiff_MethodName] = f_ptr;
}

code::Stmt* MHTranslator::createLoopMethodCall(
  std::string varname, std::string method_name, std::string argname, std::vector<int> dims) {

  assert(dims.size() > 0);

  code::Expr* ref = new code::Identifier(varname);
  int cnt = 0;
  for (auto&d : dims) {
    code::Expr* id = (d == 0 ? new code::Identifier(argname) : new code::Identifier(TEMP_LOOP_VAR_NAME + std::to_string(++cnt)));
    ref = new code::ArraySubscriptExpr(ref, id);
  }
  ref = createPtrMethodCall(ref, method_name);
  code::Stmt* ret = ref;
  for (int i = (int)dims.size() - 1; i >= 0; --i) {
    if (dims[i] != 0) {
      std::string iter_var = TEMP_LOOP_VAR_NAME + std::to_string(cnt--);
      code::DeclStmt* init = new code::DeclStmt(
        new code::VarDecl(NULL, iter_var,
          INT_TYPE, new code::IntegerLiteral(0)));
      code::Expr* cond = new code::BinaryOperator(
        new code::Identifier(iter_var),new code::IntegerLiteral(dims[i]),code::OpKind::BO_LT);
      code::Expr* step = new code::BinaryOperator(new code::Identifier(iter_var), NULL, code::OpKind::UO_INC);
      code::ForStmt* loop = new code::ForStmt(init,cond,step,ret);
      ret = loop;
    }
  }
  return ret;
}

code::Stmt* MHTranslator::createLoopNewObject(std::string store_name, std::string var_name,
  std::string lo_var, std::string hi_var, std::vector<int> dims) {
  int n = dims.size();
  // var[i][j] = new varDecl(i,j);
  code::Expr* var = new code::Identifier(store_name);
  std::vector<code::Expr*> ind;
  for (int i = 0; i < n; ++i) {
    var = new code::ArraySubscriptExpr(var, new code::Identifier(TEMP_LOOP_VAR_NAME + std::to_string(i + 1)));
    ind.push_back(new code::Identifier(TEMP_LOOP_VAR_NAME + std::to_string(i + 1)));
  }
  code::Expr* obj = new code::CallClassConstructor(code::Type(var_name), ind);

  // return statement
  code::Stmt* stmt = new code::BinaryOperator(var, new code::NewExpr(obj), code::OpKind::BO_ASSIGN);

  // generate for loops
  for (int i = n - 1; i >= 0; --i) {
    std::string iter_name = TEMP_LOOP_VAR_NAME + std::to_string(i + 1);
    // Init Statement
    code::Expr* init_val = NULL;
    if (dims[i] == 0) init_val = new code::Identifier(lo_var);
    else init_val = new code::IntegerLiteral(0);
    code::Stmt* init = new code::DeclStmt(
      new code::VarDecl(NULL,iter_name,INT_TYPE,init_val));
    // Condition
    code::Expr* upper_val = NULL;
    if (dims[i] == 0) upper_val = new code::Identifier(hi_var);
    else upper_val = new code::IntegerLiteral(dims[i]);
    code::Expr* cond = new code::BinaryOperator(new code::Identifier(iter_name), upper_val, code::OpKind::BO_LT);
    // Step
    code::Expr* step = new code::BinaryOperator(new code::Identifier(iter_name), NULL, code::OpKind::UO_INC);

    stmt = new code::ForStmt(init, cond, step, stmt);
  }

  return stmt;
}

bool MHTranslator::needExpandDepend(std::shared_ptr<ir::Clause> cls) {
  return contig_analyzer->hasSub(cls) ||
    contig_analyzer->getContig(cls).size() > 0 ||
    contig_analyzer->getChild(cls).size() > 0;
}

/////////////// END of Util Functions ///////////////////

MHTranslator::MHTranslator() {
  Translator();
  mcmc_analyzer = NULL;
  contig_analyzer = NULL;
  burnInNum = config->getIntValue("N_BURN_IN_SAMPLES"); // default is -1
  if (burnInNum < 0) {
    burnInNum = iterNum / 2;
  }
  coreQuery = code::FunctionDecl::createFunctionDecl(coreNs,CoreQueryFuncName,VOID_TYPE);
  coreStorageInit = code::FunctionDecl::createFunctionDecl(coreNs, CoreStorageInitFuncName, VOID_TYPE);
  coreWorldInit = code::FunctionDecl::createFunctionDecl(coreNs, CoreWorldInitFuncName, VOID_TYPE);
  coreGarbageCollect = code::FunctionDecl::createFunctionDecl(coreNs, CoreGarbageCollectFuncName, VOID_TYPE);
  corePrint = code::FunctionDecl::createFunctionDecl(coreNs, CorePrintFuncName, VOID_TYPE);
}

MHTranslator::~MHTranslator() {
  if(mcmc_analyzer != NULL) delete mcmc_analyzer;
  if(contig_analyzer != NULL) delete contig_analyzer;
}

/////////////////////////////////////////
////// main process start from here
//////////////////////////////////////////

void MHTranslator::translate(std::shared_ptr<swift::ir::BlogModel> model) {

  if (!init_MHTranslator(model)) return ;

  translate_fixed_part();

  translate_mcmc_data_structure();

  // set the sample algorithm selected for the MCMC framework
  setSampleAlgorithm();

  // create initStorage() and GarbageCollect()
  createStorageInit();

  translate_mcmc_obj_methods();

  translate_mcmc_query_evidences();

  // translate sampleAlg and main
  transSampleAlg();
  createMain();

  if (!errorMsg.Okay()) prog = NULL;
}

bool MHTranslator::init_MHTranslator(std::shared_ptr<swift::ir::BlogModel> model) {
  if (model->isTemporal()) {
    errorMsg.error(-1, -1, "[MCMCTranslator] : Temporal Models are not supported! Please use < PFTranslator >!");
    return false;
  }

  if (!COMPUTE_LIKELIHOOD_IN_LOG) {
    errorMsg.warning(-1, -1, "[MCMCTranslator] : [Compute in *Log* Likelihood] is *required* now! We will automatically ensure using Loglikelihood.");
    COMPUTE_LIKELIHOOD_IN_LOG = true;
  }

  this->model = model;

  prog->addOption("MCMC");

  // Special Check for Matrix Usage
  if (model->isUseMatrix())
    prog->addOption("matrix");

  // Model Analysis
  mcmc_analyzer = new analyzer::MCMCAnalyzer(model);
  if (!mcmc_analyzer->process()) {
    delete prog;
    prog = NULL; // model not valid
    return false;
  }

  // Contingency Analysis
  contig_analyzer = new analyzer::ContigAnalyzer(model);
  if (!contig_analyzer->process()) {
    delete prog;
    prog = NULL;
    return false;
  }
  return true;
}

void MHTranslator::translate_fixed_part() {
  // Add Global Constant
  transGlobalConstant();

  // Check Constant Values
  constValTable.clear();
  for (auto fun : model->getFixFuncs())
    checkConstValue(fun);

  // translate fixed function
  for (auto fun : model->getFixFuncs())
    transFixedFun(fun);
}

void MHTranslator::translate_mcmc_data_structure() {
  // create classe definitions for all random variables
  for (auto ty : model->getTypes())
    transTypeDomainDef(ty);

  // translate random function, create the corresponding class
  for (auto fun : model->getRandFuncs())
    transRandomFuncDef(fun);
}

void MHTranslator::translate_mcmc_obj_methods() {
  // translate default methods:
  //   sample()/sample_cache()/getlikeli()/getcachelikeli()
  //   active_edge()/remove_edge()
  for (auto&ty : model->getTypes()) { // Number Variables
    if (mcmc_analyzer->isOpenType(ty)) {
      // Assume only *ONE* number statement
      //  TODO: support multiple number statements
      transSampleMethod(ty->getName(), ty->getNumberStmt(0)->getBody());

      cur_context = NULL;
      cur_method_name = MCMC_GetVal_MethodName;
      // active_edge()
      transDependency(ty->getNumberStmt(0)->getBody(),
        varMethods[ty->getName()][MCMC_ActiveEdge_MethodName]->getBody(),
        MCMC_Global_AddChild_MethodName,
        MCMC_Global_AddContig_MethodName);
      // remove_edge()
      transDependency(ty->getNumberStmt(0)->getBody(),
        varMethods[ty->getName()][MCMC_RemoveEdge_MethodName]->getBody(),
        MCMC_Global_RemoveChild_MethodName,
        MCMC_Global_RemoveContig_MethodName);
    }
  }
  for (auto&fun : model->getRandFuncs()) { // For random functions
    // sample()/sample_cache()/getlikeli()/getcachelikeli()
    transSampleMethod(fun->getName(), fun->getBody());

    cur_context = NULL;
    cur_method_name = MCMC_GetVal_MethodName;
    // active_edge()
    transDependency(fun->getBody(),
      varMethods[fun->getName()][MCMC_ActiveEdge_MethodName]->getBody(),
      MCMC_Global_AddChild_MethodName,
      MCMC_Global_AddContig_MethodName);
    // remove_edge()
    transDependency(fun->getBody(),
      varMethods[fun->getName()][MCMC_RemoveEdge_MethodName]->getBody(),
      MCMC_Global_RemoveChild_MethodName,
      MCMC_Global_RemoveContig_MethodName);
  }

  // clear_prop()/ensure_support()/ensure_size()/ensure_cache()
  for (auto ty : model->getTypes()) {
    if (mcmc_analyzer->isOpenType(ty)) {
      transObjectProperty(ty, mcmc_analyzer->getDependFunc(ty));
    }
  }
}

void MHTranslator::translate_mcmc_query_evidences() {
  // translate queries
  //    include: eval_query(), print()
  transAllQuery(model->getQueries());

  // translate evidence
  //    include: initWorld(), check_obs()/update_obs()
  transAllEvidence(model->getEvidences());
}

///////////////////////////////////////////////////////////////
////////////// high level translate() ends here ///////////////
///////////////////////////////////////////////////////////////

code::Code* MHTranslator::getResult() {
  if (!errorMsg.Okay()) return NULL;

  useTag = true;
  return prog;
}

void MHTranslator::transGlobalConstant() {
  coreNs->addDecl(
    new code::VarDecl(coreNs,
    TotalRoundVarName, INT_CONST_TYPE, new code::IntegerLiteral(iterNum)));
  coreNs->addDecl(
    new code::VarDecl(coreNs,
    BurnInVarName, INT_CONST_TYPE, new code::IntegerLiteral(burnInNum)));
  coreNs->addDecl(
    new code::VarDecl(coreNs,
    RoundCounterVarName, INT_TYPE, new code::IntegerLiteral(-burnInNum)));
}

void MHTranslator::transTypeDomainDef(std::shared_ptr<ir::TypeDomain> ty) {
  const std::string& name = ty->getName();
  // create a vector containing all the names of its distinct instances
  if (ty->getInstNames().size() > 0) {
    std::string arrName = getInstanceStringArrayName(name);
    std::vector<code::Expr*> names;
    for (auto& n : ty->getInstNames())
      names.push_back(new code::StringLiteral(n));
    coreNs->addDeclFront(new code::VarDecl(coreNs, arrName, ARRAY_STRING_CONST_TYPE,
      new code::ListInitExpr(names)));
  }

  if (ty->getAllNumberStmt().size() == 0) return ;

  std::string numvar = getNameOfNumberVar(name);

  auto clsdef = code::ClassDecl::createClassDecl(coreNs, numvar, std::vector<code::Type>{NumberVar_Base_Type});
  bayesVars[name] = clsdef;

  // create class constructor
  varMethods[name][name] = code::ClassConstructor::createClassConstructor(clsdef); // empty constructor

  addDefualtMethods(name, clsdef, INT_REF_TYPE, true);

  addNumberVarSpecialMethods(name, clsdef, mcmc_analyzer->getPropSize(ty));

  // create storage
  // assume it is only a single number variable
  std::string storeName = getStoreOfNumberVar(name);
  code::VarDecl::createVarDecl(coreNs, storeName, code::Type(numvar,false,true)); // note: it is a pointer
}

void MHTranslator::transRandomFuncDef(std::shared_ptr<ir::FuncDefn> fun) {
  const std::string& name = fun->getName();
  std::string varName = getNameOfRandomVar(name);

  code::Type baseType = code::Type(code::Type(BayesVarClsName), std::vector<code::Type>{mapIRTypeToCodeType(fun->getRetTyp())});
  auto clsdef = code::ClassDecl::createClassDecl(coreNs, varName, std::vector<code::Type>{baseType});
  bayesVars[name] = clsdef;

  // create constructor
  {
    // register arguments as field members
    for (auto arg : fun->getArgs()) {
      code::VarDecl::createVarDecl(clsdef,arg->getVarName(),INT_TYPE); // assume all arguments are int!
    }
    // register constructor
    auto cons = code::ClassConstructor::createClassConstructor(clsdef);
    varMethods[name][name] = cons;
    std::vector<code::ParamVarDecl*> params;
    // Assume all the arguments are integers
    for (auto arg : fun->getArgs()) {
      params.push_back(new code::ParamVarDecl(cons,"_"+arg->getVarName(),INT_TYPE));
      cons->addInitExpr(arg->getVarName(), new code::Identifier("_" + arg->getVarName()));
    }
    cons->setParams(params); // set parameters
  }

  code::Type baseRefType = mapIRTypeToCodeType(fun->getRetTyp());
  baseRefType.setRef(true);
  addDefualtMethods(name, clsdef, baseRefType, false);

  auto retTp = fun->getRetTyp();
  if (retTp->getTyp() == ir::IRConstant::NAMETY && dynamic_cast<const ir::NameTy*>(retTp) != NULL) {
    auto ref = dynamic_cast<const ir::NameTy*>(retTp)->getRefer();
    if (ref->getAllNumberStmt().size() > 0) { // it is a object reference variable with open-type
      addObjectRefSpecialMethods(name, ref->getName(), clsdef);
    }
  }

  // create storage
  std::string storeName = getStoreOfRandomVar(name);
  if (fun->getArgs().size() > 0) { // Dynamic Table
    code::VarDecl::createVarDecl(coreNs, storeName,
      code::Type(DYNAMICTABLE_CLASS_NAME,
      std::vector<code::Type>{code::Type(varName, false, true), code::Type(std::to_string(fun->getArgs().size()))}));
  }
  else { // just a pointer
    code::VarDecl::createVarDecl(coreNs, storeName,
      code::Type(varName, false, true));
  }
}

void MHTranslator::setSampleAlgorithm() {
  // Set Algorithm for NumberVariable
  for (auto& ty : model->getTypes()) {
    if (ty->getAllNumberStmt().size() > 0) {
      std::string name = ty->getName();
      varMethods[name][MCMC_Resample_MethodName]->addStmt(
        new code::CallExpr(
          new code::Identifier(MCMC_Global_MHNumVarAlgo_MethodName),
          std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)}));
    }
  }

  // Set Algorithm for Normal Random Variable
  for (auto& fun : model->getRandFuncs()) {
    std::string name = fun->getName();
    varMethods[name][MCMC_Resample_MethodName]->addStmt(
      new code::CallExpr(
        new code::Identifier(MCMC_Global_MHAlgo_MethodName),
        std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)}));
  }
}

void MHTranslator::createStorageInit() {
  // Storage for Number Variable
  //   ==> assume it is a single pointer
  for (auto&ty : model->getTypes()) {
    if (ty->getAllNumberStmt().size() > 0) {
      std::string name = ty->getName();
      std::string varName = getNameOfNumberVar(name);
      std::string storeName = getStoreOfNumberVar(name);
      coreStorageInit->addStmt(new code::BinaryOperator(
        new code::Identifier(storeName),
        new code::NewExpr(new code::CallClassConstructor(code::Type(varName))),
        code::OpKind::BO_ASSIGN));

      // garbage collect
      coreGarbageCollect->addStmt(new code::CallExpr(
        new code::Identifier(UtilFreeObjFuncName),
        std::vector<code::Expr*>{new code::Identifier(storeName)}));
    }
  }

  // Storage for normal Random Variables
  for (auto& fun : model->getRandFuncs()) {
    std::string name = fun->getName();
    std::string varName = getNameOfRandomVar(name);
    std::string storeName = getStoreOfRandomVar(name);

    // set Garbage Collection
    coreGarbageCollect->addStmt(new code::CallExpr(
        new code::Identifier(UtilFreeObjFuncName),
        std::vector<code::Expr*>{new code::Identifier(storeName)}));

    // set Storage
    if (fun->getArgs().size() == 0) { // single pointer
      coreStorageInit->addStmt(new code::BinaryOperator(
        new code::Identifier(storeName),
        new code::NewExpr(new code::CallClassConstructor(code::Type(varName))),
        code::OpKind::BO_ASSIGN));
    }
    else { // Dynamic Table
      // resize each dimension
      bool fixed_dim = true;
      auto& argList = fun->getArgs();
      std::vector<std::string> argName;
      std::vector<int> argDim;
      for (size_t i = 0; i < argList.size(); ++i) {
        if (dynamic_cast<const ir::NameTy*>(argList[i]->getTyp()) == NULL) continue;
        auto ref = dynamic_cast<const ir::NameTy*>(argList[i]->getTyp())->getRefer();
        if (mcmc_analyzer->isOpenType(ref)) {
          fixed_dim = false;
          continue;
        }
        // resize the dimension
        int len = ref->getPreLen();
        coreStorageInit->addStmt(
            code::CallExpr::createMethodCall(
            storeName,DYNAMICTABLE_RESIZE_METHOD_NAME,
            std::vector<code::Expr*>{new code::IntegerLiteral((int)i), new code::IntegerLiteral(len)}
            )
          );

        argName.push_back(argList[i]->getVarName());
        argDim.push_back(len);
      }

      if (fixed_dim) {
        // initialize the indices of each variable
        code::CompoundStmt* context = &coreStorageInit->getBody();
        code::Expr* lhs = new code::Identifier(storeName);
        std::vector<code::Expr*> args;
        for (size_t i = 0; i < argName.size(); ++i) {
          // create nested for-loops
          auto body = new code::CompoundStmt();
          auto f_loop = new code::ForStmt(
            new code::DeclStmt(new code::VarDecl(NULL,argName[i],INT_TYPE,new code::IntegerLiteral(0))),
            new code::BinaryOperator(new code::Identifier(argName[i]),new code::IntegerLiteral(argDim[i]), code::OpKind::BO_LT),
            new code::BinaryOperator(new code::Identifier(argName[i]), NULL, code::OpKind::UO_INC),
            body);
          context->addStmt(f_loop);
          context = body;
          // create multi-index
          lhs = new code::ArraySubscriptExpr(lhs, new code::Identifier(argName[i]));
          // create multi-argument list
          args.push_back(new code::Identifier(argName[i]));
        }
        context->addStmt(
          new code::BinaryOperator(
            lhs,
            new code::NewExpr(new code::CallClassConstructor(code::Type(varName),args)),
            code::OpKind::BO_ASSIGN));
      }
    }
  }
}

void MHTranslator::transSampleMethod(std::string name, std::shared_ptr<ir::Clause> body) {
  auto&mp = varMethods[name];
  //auto&clsdef = bayesVars[name];  /*seems to be not used*/

  // translate sample()/sample_cache()/getlikeli()/getcachelikeli()
  cur_context = coreNs; // register all the distributions
  cur_constructor = &coreStorageInit->getBody(); // initialization of all static distributions
  cur_method_name = MCMC_GetVal_MethodName; // getval();
  cur_likeli_method_name = MCMC_GetLike_MethodName; // getlikeli();
  // sample()
  mp[MCMC_SampleVal_MethodName]->addStmt(transClause(body,MCMC_Val_VarName));
  cur_context = NULL;
  cur_constructor = NULL;

  // getlikeli()
  mp[MCMC_GetLike_MethodName]->addStmt(transClause(body,std::string(),MCMC_Val_VarName));

  cur_method_name = MCMC_GetCache_MethodName; // getcache()
  cur_likeli_method_name = MCMC_GetCacheLike_MethodName; // getcachelikeli()
  // sample_cache()
  mp[MCMC_SampleCache_MethodName]->addStmt(transClause(body, MCMC_Cache_VarName));

  // getcachelikeli()
  auto&ptr = mp[MCMC_GetCacheLike_MethodName];
  ptr->addStmt(new code::DeclStmt(
    new code::VarDecl(
      ptr,TEMP_VAL_NAME,AUTO_TYPE,
      new code::CallExpr(new code::Identifier(MCMC_GetCache_MethodName)))));
  ptr->addStmt(transClause(body, std::string(), TEMP_VAL_NAME));
}

void MHTranslator::transDependency(std::shared_ptr<ir::Clause> cls, code::CompoundStmt& cmp,
  std::string child_method_name, std::string contig_method_name) {
  auto&child_list = contig_analyzer->getChild(cls);
  auto&contig_list = contig_analyzer->getContig(cls);

  for (auto& v : contig_list) {
    auto var = createRandomVarRef(v);
    cmp.addStmt(createPtrMethodCall(var, contig_method_name,
      std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)}));
  }
  for (auto& v : child_list) {
    auto var = createRandomVarRef(v);
    cmp.addStmt(createPtrMethodCall(var, child_method_name,
      std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)}));
  }

  if (!contig_analyzer->hasSub(cls)) return ;

  // Translating Case/MultiCase/IfThen
  auto ifstmt = std::dynamic_pointer_cast<ir::IfThen>(cls);
  if (ifstmt != nullptr) {
    cmp.addStmt(transDependIfThen(ifstmt, child_method_name, contig_method_name));
    return ;
  }

  auto brch = std::dynamic_pointer_cast<ir::Branch>(cls);
  if (brch != nullptr) {
    cmp.addStmt(transDependBranch(brch, child_method_name, contig_method_name));
    return ;
  }

  // for normal expressions, we do nothing
  return ;
}

code::Stmt* MHTranslator::transDependIfThen(std::shared_ptr<ir::IfThen> st,
  std::string child_method_name, std::string contig_method_name) {
  code::Expr* cond = transExpr(st->getCond());
  code::CompoundStmt* ifcl = new code::CompoundStmt();
  if (st->getThen() != nullptr && needExpandDepend(st->getThen())) {
    transDependency(st->getThen(), *ifcl, child_method_name, contig_method_name);
  }
  code::CompoundStmt* elcl = NULL;
  if (st->getElse() != nullptr && needExpandDepend(st->getElse())) {
    elcl = new code::CompoundStmt();
    transDependency(st->getElse(), *elcl, child_method_name, contig_method_name);
  }
  return new code::IfStmt(cond, ifcl, elcl);
}

code::Stmt* MHTranslator::transDependBranch(std::shared_ptr<ir::Branch> br,
  std::string child_method_name, std::string contig_method_name) {
  if (br->getArgDim() > 1)
    return transDependMultiCase(br, child_method_name, contig_method_name); // Special Multi-Case Expr

  code::SwitchStmt* sst = new code::SwitchStmt(transExpr(br->getVar()));
  code::CaseStmt* cst;
  for (size_t i = 0; i < br->size(); i++) {
    if (br->getBranch(i) != nullptr && needExpandDepend(br->getBranch(i))) {
      code::CompoundStmt* cmp = new code::CompoundStmt();
      cst = new code::CaseStmt(transExpr(br->getCond(i)), cmp);
      transDependency(br->getBranch(i), *cmp, child_method_name, contig_method_name);
      sst->addStmt(cst);
      sst->addStmt(new code::BreakStmt());
    }
  }
  return sst;
}

code::Stmt* MHTranslator::transDependMultiCase(std::shared_ptr<ir::Branch> br,
  std::string child_method_name, std::string contig_method_name) {
  std::string mpName = MULTI_CASE_MAP_NAME + std::to_string((size_t)(br.get())); // Map has been registered!
  auto var = br->getVar();
  auto iter = new code::CallExpr(
    new code::BinaryOperator(
    new code::Identifier(mpName), new code::Identifier("find"), code::OpKind::BO_FIELD),
    { transExpr(var) });
  auto indx = new code::BinaryOperator(iter, new code::Identifier("second"), code::OpKind::BO_POINTER);
  code::SwitchStmt* sst = new code::SwitchStmt(indx);
  code::CaseStmt* cst;
  for (size_t i = 0; i < br->size(); i++) {
    if (br->getBranch(i) != nullptr && needExpandDepend(br->getBranch(i))) {
      code::CompoundStmt* cmp = new code::CompoundStmt();
      cst = new code::CaseStmt(new code::IntegerLiteral(i), cmp);
      transDependency(br->getBranch(i), *cmp, child_method_name, contig_method_name);
      sst->addStmt(cst);
      sst->addStmt(new code::BreakStmt());
    }
  }
  return sst;
}

void MHTranslator::transObjectProperty(std::shared_ptr<ir::TypeDomain> ty, std::vector<std::shared_ptr<ir::FuncDefn>>& funcs) {
  if (funcs.size() == 0) {// no property for this open type
    return ;
  }

  // Handle:
  //   clear_prop() / ensure_support() / ensure_size() / ensure_cache()

  std::string name = ty->getName();
  auto& mp = varMethods[name];

  // ensure_size(){ if (n > capacity) { ... }; }
  code::CompoundStmt* cmp = new code::CompoundStmt();
  code::IfStmt* ifst = new code::IfStmt(
    new code::BinaryOperator(new code::Identifier(TEMP_N_NAME), new code::Identifier(MCMC_Capacity_VarName), code::OpKind::BO_GT),
    cmp);
  mp[MCMC_EnsureSize_MethodName]->addStmt(ifst);

  for (auto& fun : funcs) {
    std::string store_name = getStoreOfRandomVar(fun->getName());

    // get loop dimensions
    std::vector<int> dims;
    for (auto&a : fun->getArgs()) {
      // TODO: to handle general integer index
      auto ref = dynamic_cast<const ir::NameTy*>(a->getTyp());
      if (ref == NULL) continue;

      if (ref->getRefer() == ty) {
        dims.push_back(0);

        // ensure_size() { ... var.resize(dim, n); ...}
        cmp->addStmt(
          code::CallExpr::createMethodCall(new code::Identifier(store_name),VECTOR_RESIZE_METHOD_NAME,
            std::vector<code::Expr*>{new code::IntegerLiteral(dims.size() - 1), new code::Identifier(TEMP_N_NAME)}));
        continue;
      }

      if (mcmc_analyzer->isOpenType(ref->getRefer())) {
        // DO NOT Support!
        errorMsg.error(-1, -1, "[MHTranslator] : We only support at most * 1 * open-type index for random function <" + fun->getName() + ">");
        continue;
      }
      // close-type
      dims.push_back(ref->getRefer()->getPreLen());
    }

    // @debug
    if (dims.size() == 0) {
      std::cerr << "Error!! for func <" << fun->getName() << " >! depend on ty <" << ty->getName() << "> dims.size() == 0"<<std::endl;
    }

    // clear_prop()
    mp[MCMC_ClearProp_MethodName]->addStmt(
      createLoopMethodCall(store_name, MCMC_Clear_MethodName, TEMP_IND_NAME, dims));
    // ensure_support()
    mp[MCMC_EnsureSupport_MethodName]->addStmt(
      createLoopMethodCall(store_name, MCMC_GetVal_MethodName, TEMP_IND_NAME, dims));
    // ensure_cache()
    mp[MCMC_EnsureCache_MethodName]->addStmt(
      createLoopMethodCall(store_name, MCMC_Global_EnsureCache_MethodName, TEMP_IND_NAME, dims));
    /*
     * ensure_size() {
     * ....
     *   for (int i = capacity; i < n; ++ i) ...
     *       var[..][i][...] = new varDecl(...,i,...)
     * ....
     * }
     */
    cmp->addStmt(createLoopNewObject(store_name, getNameOfRandomVar(fun->getName()), MCMC_Capacity_VarName, TEMP_N_NAME, dims));
  }

  // ensure_size(){ .... capacity = n}
  cmp->addStmt(new code::BinaryOperator(
    new code::Identifier(MCMC_Capacity_VarName),
    new code::Identifier(TEMP_N_NAME), code::OpKind::BO_ASSIGN));
}

void MHTranslator::transAllQuery(
  std::vector<std::shared_ptr<ir::Query> > queries) {
  /* ++ tot_round;
   * if (tot_round <= 0) return ;
   */
  coreQuery->addStmt(new code::BinaryOperator(new code::Identifier(RoundCounterVarName),NULL,code::OpKind::UO_INC));
  coreQuery->addStmt(new code::IfStmt(
    new code::BinaryOperator(new code::Identifier(RoundCounterVarName),new code::IntegerLiteral(0),code::OpKind::BO_LEQ),
    new code::ReturnStmt()));

  cur_context = NULL;
  cur_method_name = MCMC_GetVal_MethodName;
  for (size_t i = 0; i < queries.size(); ++i) {
    transQuery(coreQuery, queries[i], i);
  }
}

void MHTranslator::transQuery(code::FunctionDecl* fun, std::shared_ptr<ir::Query> qr, int n) {
  // Register Printing Hist Class
  std::string answervarname = ANSWER_VAR_NAME_PREFIX + std::to_string(n);
  // In MCMC framework, Hist does not need Logorithm computation
  std::vector<code::Expr*> initArgs{ new code::BooleanLiteral(false) };
  if (dynamic_cast<const ir::NameTy*>(qr->getVar()->getTyp()) != nullptr) {
    auto ty = dynamic_cast<const ir::NameTy*>(qr->getVar()->getTyp());
    std::string tyName = ty->getRefer()->getName();
    initArgs.push_back(new code::StringLiteral(tyName));
    if (ty->getRefer()->getInstNames().size() > 0) {
      initArgs.push_back(new code::BinaryOperator(NULL,
        new code::Identifier(getInstanceStringArrayName(tyName)), code::OpKind::UO_ADDR));
    }
  }
  // if double, push another initial argument to the Histogram constructor
  if (qr->getVar()->getTyp()->toString() == ir::IRConstString::DOUBLE) {
    initArgs.push_back(new code::IntegerLiteral(config->getIntValue("N_HIST_BUCKETS")));
  }

  code::Expr* initvalue = new code::CallClassConstructor(
      code::Type(HISTOGRAM_CLASS_NAME, std::vector<code::Type>( {
          (qr->getVar()->getTyp()->getTyp() == ir::IRConstant::BOOL ?
            BOOL_TYPE : mapIRTypeToCodeType(qr->getVar()->getTyp())) })),
          initArgs);
  // Everything same up until here
  if (qr->hasForLoop()) {
    transForloopQueryHelper(fun, qr, n, initvalue);
  } else {
    code::VarDecl::createVarDecl(
        coreNs, answervarname,
        code::Type(HISTOGRAM_CLASS_NAME, std::vector<code::Type>( {
            (qr->getVar()->getTyp()->getTyp() == ir::IRConstant::BOOL ?
              BOOL_TYPE : mapIRTypeToCodeType(qr->getVar()->getTyp())) })),
        initvalue);
    std::vector<code::Expr*> args;
    args.push_back(transExpr(qr->getVar()));
    args.push_back(new code::IntegerLiteral(1));
    fun->addStmt(
        code::CallExpr::createMethodCall(answervarname, HISTOGRAM_ADD_METHOD_NAME,
                                         args));
    // add print this result in print()
    // :::=> answer_id.print("query expr");
    corePrint->addStmt(
        code::CallExpr::createMethodCall(answervarname,
                                         HISTOGRAM_PRINT_METHOD_NAME,
                                         std::vector<code::Expr*> { new code::StringLiteral(qr->str()) }));
  }
}

void MHTranslator::transForloopQueryHelper(code::FunctionDecl* fun, std::shared_ptr<ir::Query> qr, int n, code::Expr* initvalue) {
    std::string answervarname = ANSWER_VAR_NAME_PREFIX + std::to_string(n);
    std::string buffername = "buffer" + std::to_string(n);
    // Perform initialization of Histogram DynamicTable
    std::vector<std::string> argName, vecstr_names;
    std::vector<int> argDim;
    for (int k = 0; k <= (int)qr->getArgs().size() - 1; k++) {
      auto ty = dynamic_cast<const ir::NameTy*>(qr->getArg(k)->getTyp());
      assert(ty != NULL);
      // Resize each dimension in Hist DynamicTable
      int len = ty->getRefer()->getPreLen();
      coreStorageInit->addStmt(
            code::CallExpr::createMethodCall(
            answervarname, DYNAMICTABLE_RESIZE_METHOD_NAME,
            std::vector<code::Expr*>{new code::IntegerLiteral(k), new code::IntegerLiteral(len)}
            )
        );
      vecstr_names.push_back(getInstanceStringArrayName(ty->toString()));
      argName.push_back(qr->getArg(k)->getVarName());
      argDim.push_back(len);
    }

    code::CompoundStmt* context = &coreStorageInit->getBody();
    code::Stmt* initHistStmt = new code::BinaryOperator(
        get_var_name_with_args(answervarname, argName),
        new code::NewExpr(initvalue),
        code::OpKind::BO_ASSIGN);
    initHistStmt = createMultiArgForeachLoop(argName, argDim, initHistStmt);
    context->addStmt(initHistStmt);

    // Declare Histogram Storage
    code::Type histType =
      code::Type(HISTOGRAM_CLASS_NAME,
        std::vector<code::Type>( {
          (qr->getVar()->getTyp()->getTyp() == ir::IRConstant::BOOL ?
            BOOL_TYPE : mapIRTypeToCodeType(qr->getVar()->getTyp())) }), false, true);
    code::VarDecl::createVarDecl(coreNs, answervarname,
      code::Type(DYNAMICTABLE_CLASS_NAME,
         std::vector<code::Type>{histType, code::Type(std::to_string(qr->getArgs().size()))}));

    std::vector<code::Expr*> args;
    args.push_back(transExpr(qr->getVar()));
    args.push_back(new code::IntegerLiteral(1));
    code::Stmt* evalSt = createPtrMethodCall(
        get_var_name_with_args(answervarname, argName), HISTOGRAM_ADD_METHOD_NAME, args);
    code::Stmt* printSt = new code::CompoundStmt();

    code::Expr* argstr = printer(qr->str(), vecstr_names, argName);
    ((code::CompoundStmt *) printSt)->addStmt(
        createPtrMethodCall(
            get_var_name_with_args(answervarname, argName), HISTOGRAM_PRINT_METHOD_NAME,
            std::vector<code::Expr*> { argstr })); // fix this thing
    if (qr->getCond() != nullptr) {
        evalSt = new code::IfStmt(transExpr(qr->getCond()), evalSt);
        printSt = new code::IfStmt(transExpr(qr->getCond()), printSt);
    }
    // generate eval and print for-loops
    evalSt = createMultiArgForeachLoop(argName, argDim, evalSt);
    printSt = createMultiArgForeachLoop(argName, argDim, printSt);

    fun->addStmt(evalSt);
    // corePrint->addStmt(new code::DeclStmt(
    //     new code::VarDecl(
    //         corePrint,
    //         buffername + "[256]",
    //         code::Type("char"))));
    corePrint->addStmt(printSt);
}

void MHTranslator::transAllEvidence(
  std::vector<std::shared_ptr<ir::Evidence> > evids) {
  //TODO: to use generic rejection sampling for initialization
  //      [ now we assume that no rejection is needed! ]

  cur_context = NULL;
  cur_method_name = MCMC_GetVal_MethodName;
  for (auto& evi : evids) {
    // set_evidence(evi->left, evi->right)
    code::Expr* var = createRandomVarRef(evi->getLeft());
    if (var == NULL) {
      errorMsg.error(-1, -1, "[MHTranslator] : Left side of evidence must be a random variable! < " + evi->getLeft()->toString() + " > is not allowed!");
      continue;
    }

    code::Stmt* st = new code::CallExpr(
      new code::TemplateExpr(
      new code::Identifier(UtilSetEviFuncName),
      std::vector<code::Expr*>{new code::Identifier(mapIRTypeToCodeType(evi->getLeft()->getTyp()).getName())}),
      std::vector<code::Expr*> {var, transExpr(evi->getRight())});

    // check for-loop
    if (evi->hasForLoop()) { // generate for loop
      if (evi->getCond() != nullptr) {
        st = new code::IfStmt(transExpr(evi->getCond()), st);
      }
      for (int k = (int)evi->getArgs().size() - 1; k >= 0; --k) {
        // everything is nameTy
        auto ty = dynamic_cast<const ir::NameTy*>(evi->getArg(k)->getTyp());
        assert(ty != NULL);
        code::Expr* loop_n = NULL;
        if (ty->getRefer()->getNumberStmtSize() == 0)
          loop_n = new code::IntegerLiteral(ty->getRefer()->getPreLen());
        else {
          std::string numvarstore = getStoreOfNumberVar(ty->getRefer()->getName());
          loop_n = createPtrMethodCall(new code::Identifier(numvarstore), MCMC_GetVal_MethodName);
        }
        assert(loop_n != NULL);
        st = createForeachLoop(evi->getArg(k)->getVarName(), loop_n, st, false, true);
      }
    }
    coreWorldInit->addStmt(st);

    // check_obs() / update_obs()
    auto& contig_list = contig_analyzer->getContig(evi->getLeft());
    if (contig_list.size() != 0) {
      // When there is a switching variable on the left side, we do not allow for-loop
      assert(!evi->hasForLoop());

      for (auto& v : contig_list) {
        std::string name = getRandomVarRefName(v);
        if (name.size() == 0) continue;

        // assert(name.size() > 0);
        addEvidenceCheckSpecialMethods(name, bayesVars[name]); // register methods: check_obs()/update_obs(bool flag)

        auto&mp = varMethods[name];
        // bool check_obs() {if (var != evi) return false; ....}
        mp[MCMC_CheckObs_MethodName]->addStmt(new code::IfStmt(
          new code::BinaryOperator(transExpr(evi->getLeft()), transExpr(evi->getRight()), code::OpKind::BO_NEQ),
          new code::ReturnStmt(new code::BooleanLiteral(false))));

        // void update_obs(bool flag) {util_update_obs(var, flag);}
        mp[MCMC_UpdateObs_MethodName]->addStmt(new code::CallExpr(
          new code::Identifier(UtilUpdateObsFuncName),
          std::vector<code::Expr*> {createRandomVarRef(evi->getLeft()), new code::Identifier(TEMP_FLAG_NAME)}));
      }
    }
  }

  // add default return true for all check_obs()
  for (auto&var : varMethods) {
    if (var.second.count(MCMC_CheckObs_MethodName) > 0) {
      var.second[MCMC_CheckObs_MethodName]->addStmt(new code::ReturnStmt(new code::BooleanLiteral(true)));
    }
  }
}

code::FunctionDecl* MHTranslator::transSampleAlg() {
  // general framework of MCMC sampling
  /*
   *  for(int loop = 0; loop < LOOP; ++ loop) {mcmc_sample_single_iter(); eval_query();}
   *  print();
   */
  SAMPLEFUN fun = DECLARE_SAMPLEFUN();
  code::CompoundStmt* cmp = new code::CompoundStmt();
  cmp->addStmt(new code::CallExpr(new code::Identifier(MCMCResampleFuncName)));
  cmp->addStmt(new code::CallExpr(new code::Identifier(CoreQueryFuncName)));

  code::Stmt* loop = new code::ForStmt(
    new code::BinaryOperator(new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME), new code::IntegerLiteral(1), code::OpKind::BO_ASSIGN),
    new code::BinaryOperator(new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME), new code::Identifier(TotalRoundVarName), code::OpKind::BO_LEQ),
    new code::BinaryOperator(new code::Identifier(CURRENT_SAMPLE_NUM_VARNAME), NULL, code::OpKind::UO_INC),
    cmp);

  fun->addStmt(loop);

  return fun;
}

void MHTranslator::createMain() {
  mainFun = code::FunctionDecl::createFunctionDecl(prog, MAIN_FUN_NAME,
                                                   INT_TYPE);
  /*  swift::initStorage();
   *  swift::initWorld();
   *   >>>> print Init Time
   *  swift::main_samle_algorithm();
   *   >>>> print Sampling time
   *  swift::GarbageCollect();
   */
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

  mainFun->addStmt(
    new code::BinaryOperator(new code::Identifier(MAIN_NAMESPACE_NAME),
    new code::CallExpr(new code::Identifier(CoreStorageInitFuncName)),code::OpKind::BO_SCOPE)
  );
  mainFun->addStmt(
    new code::BinaryOperator(new code::Identifier(MAIN_NAMESPACE_NAME),
    new code::CallExpr(new code::Identifier(CoreWorldInitFuncName)),code::OpKind::BO_SCOPE)
  );

  // calculate duration for init time
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
          new code::StringLiteral("\\ninit time: %fs\\n"),
          code::CallExpr::createMethodCall("__elapsed_seconds", "count") }));
  mainFun->addStmt(st);


  // record start time for sample algorithm
  st = new code::BinaryOperator(
    new code::Identifier("__start_time"),
    new code::CallExpr(
      new code::Identifier("std::chrono::system_clock::now")),
      code::OpKind::BO_ASSIGN);
  mainFun->addStmt(st);

  // main sample algorithm
  mainFun->addStmt(
    new code::BinaryOperator(new code::Identifier(MAIN_NAMESPACE_NAME),
    new code::CallExpr(new code::Identifier(MAIN_SAMPLING_FUN_NAME)),code::OpKind::BO_SCOPE)
  );

  // calculate duration for sample time
  st = new code::BinaryOperator(
    new code::Identifier("__elapsed_seconds"),
    new code::BinaryOperator(
      new code::CallExpr(
      new code::Identifier("std::chrono::system_clock::now")),
      new code::Identifier("__start_time"), code::OpKind::BO_MINUS),
    code::OpKind::BO_ASSIGN);
  mainFun->addStmt(st);

  st = new code::CallExpr(
      new code::Identifier("printf"), std::vector<code::Expr*>( {
          new code::StringLiteral("\\nsample time: %fs (#iter = %d)\\n"),
          code::CallExpr::createMethodCall("__elapsed_seconds", "count"),
          new code::IntegerLiteral(iterNum)}));
  mainFun->addStmt(st);

  // Print Result
  mainFun->addStmt(
    new code::BinaryOperator(new code::Identifier(MAIN_NAMESPACE_NAME),
    new code::CallExpr(new code::Identifier(CorePrintFuncName)), code::OpKind::BO_SCOPE)
  );

  // GarbageCollection
  mainFun->addStmt(
    new code::BinaryOperator(new code::Identifier(MAIN_NAMESPACE_NAME),
    new code::CallExpr(new code::Identifier(CoreGarbageCollectFuncName)),code::OpKind::BO_SCOPE)
  );
}


/////////////// Translation of clause and expression ////////////////////////

code::FunctionDecl* MHTranslator::transFixedFun(
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

  // Check whether need to do memorization
  std::vector<int> dims;
  if (!fd->isTemporal() &&  // Do not support temporal variable
      checkFixedFunNeedMemo(fd, dims)) {
    // register memozization cache
    std::vector<code::Expr*> args;
    for (auto&d : dims) {
      args.push_back(new code::IntegerLiteral(d));
    }
    code::VarDecl::createVarDecl(
      coreNs, getValueVarName(fixedfunname),
      args, valuetype);
    args.clear(); // Attention: we need to create args twice!
    for (auto&d : dims) {
      args.push_back(new code::IntegerLiteral(d));
    }
    code::VarDecl::createVarDecl(
      coreNs, getMarkVarName(fixedfunname),
      args, BOOL_TYPE);

    if (isObjectType(fd->getRetTyp()))
      valuetype.setRef(true);
  }
  else
    dims.clear();

  // adding method declaration in the main class
  code::FunctionDecl* fixedfun = code::FunctionDecl::createFunctionDecl(
    coreNs, fixedfunname, valuetype);
  fixedfun->setParams(transParamVarDecls(fixedfun, fd));
  declared_funs[fixedfun->getName()] = fixedfun;

  if (dims.size() > 0) { // need memorization
    code::Expr* tar = NULL;
    code::Type valueRefType = valuetype;
    valueRefType.setRef(true);
    // create mark ref var
    tar = new code::Identifier(getMarkVarName(fixedfunname));
    for (auto& prm : fixedfun->getParams()) {
      code::Expr* sub = new code::Identifier(prm->getId());
      tar = new code::ArraySubscriptExpr(tar, sub);
    }
    fixedfun->addStmt(new code::DeclStmt(
      new code::VarDecl(fixedfun,MARK_VAR_REF_NAME,BOOL_REF_TYPE,tar)));
    // create value ref var
    tar = new code::Identifier(getValueVarName(fixedfunname));
    for (auto& prm : fixedfun->getParams()) {
      code::Expr* sub = new code::Identifier(prm->getId());
      tar = new code::ArraySubscriptExpr(tar, sub);
    }
    fixedfun->addStmt(new code::DeclStmt(new code::VarDecl(fixedfun, VALUE_VAR_REF_NAME, valueRefType, tar)));

    code::Expr* cond = new code::Identifier(MARK_VAR_REF_NAME);
    code::IfStmt* stmt = new code::IfStmt(
      cond,
      new code::ReturnStmt(new code::Identifier(VALUE_VAR_REF_NAME)));
    fixedfun->addStmt(stmt);
    fixedfun->addStmt(new code::BinaryOperator(
      new code::Identifier(MARK_VAR_REF_NAME),
      new code::BooleanLiteral(true),
      code::OpKind::BO_ASSIGN));
  }

  code::Expr* retExpr = NULL;
  if (std::dynamic_pointer_cast<ir::Expr>(fd->getBody()) != nullptr) {
    retExpr = transExpr(std::dynamic_pointer_cast<ir::Expr>(fd->getBody()));
  }
  else {
    code::VarDecl::createVarDecl(fixedfun, VALUE_VAR_REF_NAME, mapIRTypeToCodeType(fd->getBody()->getTyp()));
    fixedfun->addStmt(
      transClause(fd->getBody(), VALUE_VAR_REF_NAME));
    retExpr = new code::Identifier(VALUE_VAR_REF_NAME);
  }
  // when memorization we need to update the value reference
  if (dims.size() > 0) {
    fixedfun->addStmt(
      new code::BinaryOperator(
      new code::Identifier(VALUE_VAR_REF_NAME),
      retExpr, code::OpKind::BO_ASSIGN));
    retExpr = new code::Identifier(VALUE_VAR_REF_NAME);
  }
  fixedfun->addStmt(new code::ReturnStmt(retExpr));
  return fixedfun;
}

code::Stmt* MHTranslator::transClause(std::shared_ptr<ir::Clause> clause,
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
      return new code::BinaryOperator(
        new code::Identifier(retvar),
        transExpr(expr, valuevar),
        code::OpKind::BO_ASSIGN);
    }
    else {
      return new code::ReturnStmt(transExpr(expr, valuevar));
    }
    // TODO no 100% correct here why??
  }
  // should not reach here!
  assert(false);
  return NULL;
}

code::ParamVarDecl* MHTranslator::transParamVarDecl(
    code::DeclContext* context, const std::shared_ptr<ir::VarDecl> var) {
  return new code::ParamVarDecl(context, var->getVarName(),
                                mapIRTypeToCodeType(var->getTyp()));
}

std::vector<code::ParamVarDecl*> MHTranslator::transParamVarDecls(
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

code::Stmt* MHTranslator::transMultiCaseBranch(std::shared_ptr<ir::Branch> br,
  std::string retvar,
  std::string valuevar) {
  std::string mpName = MULTI_CASE_MAP_NAME + std::to_string((size_t)(br.get()));
  auto var = br->getVar();
  if (cur_context != NULL) {
    // need to register a const map for indexing
    code::Type baseTy = mapIRTypeToCodeType(var->getTyp(), false, false);
    // Construct the corresponding MapInit Expr
    auto mex = std::make_shared<ir::MapExpr>();
    mex->setFromTyp(br->getCond(0)->getTyp());
    mex->setToTyp(br->getBranch(0)->getTyp());
    for (size_t i = 0; i < br->getConds().size(); ++i) {
      mex->addMap(br->getCond(i), std::make_shared<ir::IntLiteral>(i));
    }
    code::VarDecl::createVarDecl(
      cur_context, mpName, code::Type(MAP_BASE_TYPE, std::vector<code::Type>({ baseTy, INT_TYPE }), false, false, true),
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

code::Stmt* MHTranslator::transBranch(std::shared_ptr<ir::Branch> br,
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

code::Stmt* MHTranslator::transIfThen(std::shared_ptr<ir::IfThen> ith,
                                       std::string retvar,
                                       std::string valuevar) {
  code::Expr* cond = transExpr(ith->getCond());
  code::Stmt* ifcl = transClause(ith->getThen(), retvar, valuevar);
  code::Stmt* elcl = NULL;
  if (ith->getElse())
    elcl = transClause(ith->getElse(), retvar, valuevar);
  return new code::IfStmt(cond, ifcl, elcl);
}

code::Expr* MHTranslator::transExpr(std::shared_ptr<ir::Expr> expr,
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
    valuevar = ""; // TODO: in general
  }

  // translate origin function call
  std::shared_ptr<ir::OriginRefer> oriref = std::dynamic_pointer_cast<
      ir::OriginRefer>(expr);
  if (oriref) {
    res = transOriginRefer(oriref, valuevar);

    errorMsg.error(-1, -1, "[MHTranslator] : [Origin Function] is not supported now!");
  }

  // translate quantified formula
  std::shared_ptr<ir::QuantForm> form =
      std::dynamic_pointer_cast<ir::QuantForm>(expr);
  if (form != nullptr && args.size() == 1) {
    used = true;
    res = transQuantForm(form, args[0]);

    errorMsg.error(-1, -1, "[MHTranslator] : [Quantitative Formula (forall, exist)] is not supported now!");
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
    } else
    if (expr->getTyp() != NULL && expr->getTyp()->getTyp() == ir::IRConstant::DOUBLE) {
      auto diff = new code::BinaryOperator(new code::Identifier(valuevar), res, code::OpKind::BO_MINUS);
      auto abs_norm = new code::CallExpr(new code::Identifier("fabs"), std::vector<code::Expr*>{diff});
      res = new code::BinaryOperator(abs_norm, new code::FloatingLiteral(ZERO_EPS), code::OpKind::BO_LEQ);
    } else
      res = new code::BinaryOperator(new code::Identifier(valuevar), res, code::OpKind::BO_EQU);

    // Compute LogLikelihood
    if (COMPUTE_LIKELIHOOD_IN_LOG) {
      std::vector<code::Expr*> cmparg;
      cmparg.push_back(res);
      cmparg.push_back(new code::BooleanLiteral(true));
      res = new code::CallExpr(new code::Identifier(LOG_EQUAL_FUN_NAME),
            cmparg);
    }
  }

  // TODO translate other expression
  // if valuevar is provided it should be
  if (!used)
    for (auto ag : args)
      delete ag;
  return res;
}

code::Expr* MHTranslator::transOriginRefer(
    std::shared_ptr<ir::OriginRefer> originref, std::string valuevar) {
  // TODO: do not support now! Should not reach here!
  assert(false);
  return NULL;
}

code::Expr* MHTranslator::transCardExpr(std::shared_ptr<ir::CardExpr> cardexp,
                                         std::string valuevar,
                                         bool is_return_value) {
  std::shared_ptr<ir::CondSet> setexp = std::dynamic_pointer_cast<ir::CondSet>(
      cardexp->getBody());
  assert(setexp);
  // Note: For CardExpr, we can directly ignore the func field of this SetExpr

  // can only handle conditional set for the moment.
  std::shared_ptr<ir::VarDecl> var = setexp->getVar();
  const ir::NameTy* tp = dynamic_cast<const ir::NameTy*>(var->getTyp());
  assert(tp);

  if (tp->getRefer()->getAllNumberStmt().size() == 0) {
    // no number statement
    code::Expr* num = new code::IntegerLiteral(tp->getRefer()->getPreLen());
    if (valuevar.size() != 0)  {
      if (COMPUTE_LIKELIHOOD_IN_LOG) {
        num = new code::CallExpr(
          new code::Identifier(LOG_EQUAL_FUN_NAME),
          std::vector<code::Expr*>{num, new code::Identifier(valuevar)});
      }
      else {
        num = new code::BinaryOperator(num, new code::Identifier(valuevar), code::OpKind::BO_EQU);
      }
    }
    return num;
  }

  // can only handle name type for the moment
  std::string tyname = tp->getRefer()->getName();
  std::string numvarstore = getStoreOfNumberVar(tyname);

  if (!setexp->getCond()) {
    // empty condition
    // ::: ==> numvar->cur_method()
    if (valuevar.size() == 0) {
      code::Expr* ret = new code::Identifier(numvarstore);
      if (is_return_value) {
        ret = createPtrMethodCall(ret, cur_method_name);
      }
      return ret;
    }
    else { // compute likelihood
      return createPtrMethodCall(new code::Identifier(numvarstore), cur_likeli_method_name);
    }
  }

  // Count the cardinality of a cond set
  //  ::: ==> _count(numvar->cur_method(), func)
  //  where func is a lambda expression translated from setexp->getCond();
  auto func = new code::LambdaExpr(code::LambdaKind::REF, BOOL_TYPE);
  func->addStmt(new code::ReturnStmt(transExpr(setexp->getCond())));
  std::vector<code::Expr*> args;
  args.push_back(createPtrMethodCall(new code::Identifier(numvarstore), cur_method_name));
  args.push_back(func);
  code::Expr* res = new code::CallExpr(new code::Identifier(FILTER_COUNT_NAME),
                                       args);

  if (valuevar.size() != 0) {
    if (COMPUTE_LIKELIHOOD_IN_LOG) {
      res = new code::CallExpr(
        new code::Identifier(LOG_EQUAL_FUN_NAME),
        std::vector<code::Expr*>{res, new code::Identifier(valuevar)});
    }
    else {
      res = new code::BinaryOperator(res, new code::Identifier(valuevar), code::OpKind::BO_EQU);
    }
  }

  return res;
}

code::Expr* MHTranslator::transSetExpr(std::shared_ptr<ir::SetExpr> e) {
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

  if (condset->getCond() != nullptr) {
    errorMsg.warning(-1, -1, "[MHTranslator] : [General Set Expression] is not fully supported! Might lead to error result!");
  }

  std::shared_ptr<ir::VarDecl> var = condset->getVar();
  const ir::NameTy* tp = dynamic_cast<const ir::NameTy*>(var->getTyp());
  assert(tp != NULL);
  std::string tyname = tp->getRefer()->getName();
  std::string numvarstore = getStoreOfNumberVar(tyname);

  code::Expr* tot_inst =
    (tp->getRefer()->getNumberStmtSize() > 0 ?
     createPtrMethodCall(new code::Identifier(numvarstore), cur_method_name) :
     new code::IntegerLiteral(tp->getRefer()->getPreLen()));

  std::vector<code::Expr*> args;
  args.push_back(tot_inst);

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
 *        _forall(numvar->cur_method(), [&](int a)->bool{return cond(a);})
 */
code::Expr* MHTranslator::transQuantForm(std::shared_ptr<ir::QuantForm> qt, code::Expr* cond) {
  std::string func = qt->isForall() ? FORALL_NAME : EXISTS_NAME;
  auto var = qt->getVar();

  auto tp = dynamic_cast<const ir::NameTy*>(var->getTyp());
  assert(tp);

  std::string tyname = tp->getRefer()->getName();
  std::string numvarstore = getStoreOfNumberVar(tyname);

  code::Expr* num =
    (tp->getRefer()->getNumberStmtSize() > 0 ?
    createPtrMethodCall(new code::Identifier(numvarstore), cur_method_name) :
    new code::IntegerLiteral(tp->getRefer()->getPreLen()));

  auto lambda = new code::LambdaExpr();
  lambda->setType(BOOL_TYPE);
  lambda->addParam(new code::ParamVarDecl(lambda, var->getVarName(), INT_TYPE));
  lambda->addStmt(new code::ReturnStmt(cond));
  return new code::CallExpr(new code::Identifier(func), std::vector<code::Expr*>{num, lambda});
}

code::Expr* MHTranslator::transMapExpr(std::shared_ptr<ir::MapExpr> mex) {
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
  code::Type maptype(MAP_BASE_TYPE, { fromType, toType });
  return new code::CallClassConstructor(maptype, maparg);
}

code::Expr* MHTranslator::transOprExpr(std::shared_ptr<ir::OprExpr> opr,
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

code::Expr* MHTranslator::transArrayExpr(std::shared_ptr<ir::ArrayExpr> opr,
  std::vector<code::Expr*> args) {
  std::vector<code::Expr*> sub{ new code::ListInitExpr(args) };
  return new code::CallClassConstructor(mapIRTypeToCodeType(opr->getTyp()),sub);
}

code::Expr* MHTranslator::transMatrixExpr(std::shared_ptr<ir::MatrixExpr> mat) {
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

code::Expr* MHTranslator::transDistribution(
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
    std::string tyname = tp->getRefer()->getName();
    std::string numvarstore = getStoreOfNumberVar(tyname);
    code::Expr* num =
      (tp->getRefer()->getNumberStmtSize() == 0 ?
       new code::IntegerLiteral(tp->getRefer()->getPreLen()):
       createPtrMethodCall(new code::Identifier(numvarstore), cur_method_name));

    if (setexp->getCond() == nullptr && setexp->getFunc() == nullptr) {
      // if there is no condition
      std::string distvarname = UNIFORM_INT_DISTRIBUTION_NAME
          + std::to_string((size_t) &(dist->getArgs()));
      if (valuevar.empty()) {
        // sample value
        // define a field in the current bayesvar class corresponding to the distribution
        if (cur_context != NULL) {
          code::VarDecl::createVarDecl(
            cur_context, distvarname, code::Type(UNIFORM_INT_DISTRIBUTION_NAME));
        }
        // put init just before sampling
        // :::=> dist.init(0, get_num_of_type - 1)
        code::Expr* callinit = code::CallExpr::createMethodCall(
            distvarname,
            DISTRIBUTION_INIT_FUN_NAME,
            std::vector<code::Expr*>(
                { new code::IntegerLiteral(0),
                  new code::BinaryOperator( num, new code::IntegerLiteral(1), code::OpKind::BO_MINUS) }));
        // :::=> dist.gen()
        code::Expr* callgen = code::CallExpr::createMethodCall(
            distvarname, DISTRIBUTION_GEN_FUN_NAME);

        if (tp->getRefer()->getNumberStmtSize() == 0) {
          if(cur_constructor != NULL) cur_constructor->addStmt(callinit);
          return callgen;
        }
        else {
          // :::=> dist.init(...), dist.gen()
          return new code::BinaryOperator(callinit, callgen,
            code::OpKind::BO_COMMA);
        }
      } else {
        // calculating likelihood
        // put init just before sampling
        // :::=> dist.init(0, get_num_of_type)
        code::Expr* callinit = code::CallExpr::createMethodCall(
            distvarname,
            DISTRIBUTION_INIT_FUN_NAME,
            std::vector<code::Expr*>(
                { new code::IntegerLiteral(0), new code::BinaryOperator(
                    num,
                    new code::IntegerLiteral(1), code::OpKind::BO_MINUS) }));
        // :::=> dist.loglikeli(valuevar)
        code::Expr* calllikeli = code::CallExpr::createMethodCall(
            distvarname,
            COMPUTE_LIKELIHOOD_IN_LOG ?
                DISTRIBUTION_LOGLIKELI_FUN_NAME : DISTRIBUTION_LIKELI_FUN_NAME,
            std::vector<code::Expr*>( { new code::Identifier(valuevar) }));
        // :::=> dist.init(...), dist.loglikeli()
        if (tp->getRefer()->getNumberStmtSize() == 0) {
          delete callinit;
          return calllikeli;
        }
        else {
          return new code::BinaryOperator(callinit, calllikeli,
            code::OpKind::BO_COMMA);
        }
      }
    } else {
      // Note: Actually, it is a general way of dynamic initialization
      std::string distvarname = UNIFORM_CHOICE_DISTRIBUTION_NAME
          + std::to_string((size_t) &(dist->getArgs()));
      if (valuevar.empty()) {
        // Sample value from the distribution
        // define a field in the main class corresponding to the distribution
        if (cur_context != NULL) {
          code::VarDecl::createVarDecl(
            cur_context, distvarname, code::Type(UNIFORM_CHOICE_DISTRIBUTION_NAME));
        }
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
  if (cur_context != NULL) {
    code::VarDecl::createVarDecl(cur_context, distvarname, code::Type(name));
  }
  if (dist->isArgRandom() || dist->hasOpenVarRef()) {
    if (valuevar.empty()) {
      // Sample value from the distribution
      // define a field in the main class corresponding to the distribution
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
      //put initialization in coreClasInit
      if (cur_constructor != NULL) {
        cur_constructor->addStmt(
          code::CallExpr::createMethodCall(distvarname,
          DISTRIBUTION_INIT_FUN_NAME, args));
      }
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

code::Expr* MHTranslator::transConstSymbol(
    std::shared_ptr<ir::ConstSymbol> cs) {
  std::shared_ptr<ir::InstSymbolRef> isr = std::dynamic_pointer_cast<
      ir::InstSymbolRef>(cs);
  if (isr) {
    return new code::IntegerLiteral((int) (isr->getInst()->getID()));
  }
  std::shared_ptr<ir::BoolLiteral> bl = std::dynamic_pointer_cast<
      ir::BoolLiteral>(cs);
  if (bl) {
    return new code::IntegerLiteral(bl->getValue());
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

code::Expr* MHTranslator::transFunctionCall(
    std::shared_ptr<ir::FunctionCall> fc, std::vector<code::Expr*> args,
    bool is_return_value) {
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
    return new code::CallExpr(new code::Identifier(fc->getName()), args);
  }

  std::string name = fc->getRefer()->getName();

  if (fc->getKind() == ir::IRConstant::FIXED) {
    if (!fc->getRefer()->isExtern()) {
      name = getFixedFunName(name);
      if (constValTable.count(name) > 0 && args.size() == 0) {
        // This fixed function is actually a constant variable
        return new code::Identifier(name);
      }
    }
    return new code::CallExpr(new code::Identifier(name), args);
  }

  if (fc->getKind() == ir::IRConstant::RANDOM) {
    code::Expr* ret = new code::Identifier(getStoreOfRandomVar(name));
    for (auto&a : args) {
      ret = new code::ArraySubscriptExpr(ret,a);
    }
    if (is_return_value) {
      ret = createPtrMethodCall(ret, cur_method_name);
    }

    return ret;
  }

  return nullptr;
}

inline SAMPLEFUN MHTranslator::DECLARE_SAMPLEFUN() {
  // declare the sample method within coreNs
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(
      coreNs, MAIN_SAMPLING_FUN_NAME, VOID_TYPE);
  return fun;
}

} /* namespace codegen */
} /* namespace swift */

