/*
 * MHTranslator.h
 *
 *  Created on: Apr 15, 2015
 *      Author: yiwu
 */

#pragma once

#include "Translator.h"
#include <map>
#include <memory>
#include <set>
#include <string>
#include "../analyzer/MCMCAnalyzer.h"
#include "../analyzer/ContigAnalyzer.h"

namespace swift {
namespace codegen {

class MHTranslator: public swift::codegen::Translator {
public:
  MHTranslator();
  virtual ~MHTranslator();
  void translate(std::shared_ptr<swift::ir::BlogModel> model);
  code::Code* getResult();

protected:
  /*
   * Translation Steps called in translate()
   */
  virtual bool init_MHTranslator(std::shared_ptr<swift::ir::BlogModel> model);
  virtual void translate_fixed_part();
  virtual void translate_mcmc_data_structure();
  virtual void translate_mcmc_obj_methods();
  virtual void translate_mcmc_query_evidences();

  analyzer::MCMCAnalyzer* mcmc_analyzer;
  analyzer::ContigAnalyzer* contig_analyzer;

  int burnInNum; // default 500000 (see Configuration)

  // All the bayesVar to declare
  std::map<std::string, code::ClassDecl*> bayesVars;

  // The function declaration for each random varibales
  std::map<std::string, std::map<std::string, code::FunctionDecl*> > varMethods;

  // Main Functions
  code::FunctionDecl* coreQuery;
  code::FunctionDecl* coreStorageInit;
  code::FunctionDecl* coreWorldInit;
  code::FunctionDecl* coreGarbageCollect;
  code::FunctionDecl* corePrint;

  // Global Function Name
  static const std::string CoreQueryFuncName;
  static const std::string CoreStorageInitFuncName;
  static const std::string CoreWorldInitFuncName;
  static const std::string CoreGarbageCollectFuncName;
  static const std::string CorePrintFuncName;
  static const std::string MCMCResampleFuncName; // this function is from MCMC.h

  // Global Class/Var Name
  static const std::string BayesVarClsName;
  static const std::string ActiveListName;
  static const std::string RoundCounterVarName;
  static const std::string TotalRoundVarName;
  static const std::string BurnInVarName;

  // BayesVar Method Name
  static const std::string MCMC_Global_MHAlgo_MethodName;
  static const std::string MCMC_Global_MHNumVarAlgo_MethodName;
  static const std::string MCMC_Global_Clear_MethodName;
  static const std::string MCMC_Global_GetVal_MethodName;
  static const std::string MCMC_Global_GetCache_MethodName;
  static const std::string MCMC_Global_EnsureCache_MethodName;
  static const std::string MCMC_Global_GetValNumVar_MethodName;
  static const std::string MCMC_Global_GetCacheNumVar_MethodName;
  static const std::string MCMC_Global_AddChild_MethodName;
  static const std::string MCMC_Global_RemoveChild_MethodName;
  static const std::string MCMC_Global_AddContig_MethodName;
  static const std::string MCMC_Global_RemoveContig_MethodName;
  static const std::string MCMC_GetName_MethodName;
  static const std::string MCMC_Resample_MethodName;
  static const std::string MCMC_Clear_MethodName;
  static const std::string MCMC_GetVal_MethodName;
  static const std::string MCMC_GetCache_MethodName;
  static const std::string MCMC_SampleVal_MethodName;
  static const std::string MCMC_SampleCache_MethodName;
  static const std::string MCMC_GetLike_MethodName;
  static const std::string MCMC_GetCacheLike_MethodName;
  static const std::string MCMC_ActiveEdge_MethodName;
  static const std::string MCMC_RemoveEdge_MethodName;
  //   ==> Evidence Related
  static const std::string MCMC_CheckObs_MethodName;
  static const std::string MCMC_UpdateObs_MethodName;
  //   ==> Number Variable Related
  static const std::string MCMC_GetPropSize_MethodName;
  static const std::string MCMC_UpdateRef_MethodName;
  static const std::string MCMC_ClearRef_MethodName;
  static const std::string MCMC_CalcRefDiff_MethodName;
  static const std::string MCMC_EnsureSize_MethodName;
  static const std::string MCMC_EnsureSupport_MethodName;
  static const std::string MCMC_EnsureCache_MethodName;
  static const std::string MCMC_ClearProp_MethodName;

  // BayesVar member variable
  static const std::string MCMC_Val_VarName;
  static const std::string MCMC_Cache_VarName;
  static const std::string MCMC_CachedFlag_VarName;
  static const std::string MCMC_ActiveFlag_VarName;
  static const std::string MCMC_ObsFlag_VarName;
  // ==> Number Variable Related
  static const std::string MCMC_Capacity_VarName;

  // Temp variable
  static const std::string TEMP_N_NAME;
  static const std::string TEMP_FROM_NAME;
  static const std::string TEMP_TO_NAME;
  static const std::string TEMP_IND_NAME;
  static const std::string TEMP_VAL_NAME;
  static const std::string TEMP_FLAG_NAME;
  static const std::string TEMP_LOOP_VAR_NAME;

  // Util Func Name
  static const std::string UtilSetEviFuncName;
  static const std::string UtilUpdateRefFuncName;
  static const std::string UtilUpdateObsFuncName;
  static const std::string UtilClearRefFuncName;
  static const std::string UtilCalcRefDiffFuncName;
  static const std::string UtilFreeObjFuncName;


  // Predefined Types
  static const code::Type NumberVar_Base_Type;


  ////////////////////////////////////////////////
  // Util Functions for MCMC
  ////////////////////////////////////////////////
  std::string getNameOfNumberVar(std::string name);
  std::string getStoreOfNumberVar(std::string name);
  std::string getNameOfRandomVar(std::string name);
  std::string getStoreOfRandomVar(std::string name);

  // create method call for a pointer
  code::Expr* createPtrMethodCall(code::Expr* ptr, std::string method_name,
    std::vector<code::Expr*> args = std::vector<code::Expr*>());

  // create a reference to a random variable
  code::Expr* createRandomVarRef(std::shared_ptr<ir::Expr> expr);

  // get the random function name corresponding to the expression
  std::string getRandomVarRefName(std::shared_ptr<ir::Expr> expr);

  void addDefualtMethods(std::string name, code::ClassDecl* clsdef, code::Type clsValRefType, bool isNumberVar);
  void addNumberVarSpecialMethods(std::string name, code::ClassDecl* clsdef, int prop_size);
  void addObjectRefSpecialMethods(std::string name, std::string objTypeName, code::ClassDecl* clsdef);
  void addEvidenceCheckSpecialMethods(std::string name, code::ClassDecl* clsdef);

  // util function for ensure_clear(), ensure_cache(), ensure_support()
  /*
   * @param: storage variable name
   * @param: method name
   * @param: refering the current index, default = TEMP_IND_NAME("_i")
   * @param: dimensions of indices, if dim[k]==0, then k-th dim is denoted by argname
   * @return: the generated for loop
   */
  code::Stmt* createLoopMethodCall(std::string varname, std::string method_name, std::string argname, std::vector<int> dims);
  // util function for ensure_size()
  /*
  * @param: storage variable name
  * @param: variable class name
  * @param: lower bound looping range, default = MCMC_Capacity_var("capapcity")
  * @param: upper bound looping range, default = TEMP_N_VAR_NAME("_n")
  * @param: dimensions of indices, if dims[i]==0, that dimension should range from lo to hi
  */
  code::Stmt* createLoopNewObject(std::string store_name, std::string var_name,
    std::string lo_var, std::string hi_var, std::vector<int> dims);

  // Check whether need expand cls to fill active_edge()/remove_edge()
  bool needExpandDepend(std::shared_ptr<ir::Clause> cls);

  ///////////////////////////////////////////////////////////////////
  //     Core methods start from here
  ///////////////////////////////////////////////////////////////////

  // Add Constant Values
  virtual void transGlobalConstant();

  // create class def for number variable
  virtual void transTypeDomainDef(std::shared_ptr<ir::TypeDomain> ty);

  // create class def for normal random variable
  virtual void transRandomFuncDef(std::shared_ptr<ir::FuncDefn> fun);

  // set function call in the method of mcmc_resample()
  virtual void setSampleAlgorithm();

  // create storage initialization
  virtual void createStorageInit();

  // translate sample()/sample_cache()/getlikeli()/getcachelikeli()
  void transSampleMethod(std::string name, std::shared_ptr<ir::Clause> body);

  // translate active_edge()/remove_edge()
  void transDependency(std::shared_ptr<ir::Clause> cls,
                        code::CompoundStmt& cmp,
                        std::string child_method_name,
                        std::string contig_method_name);

  code::Stmt* transDependIfThen(std::shared_ptr<ir::IfThen> st, std::string child_method_name, std::string contig_method_name);

  code::Stmt* transDependBranch(std::shared_ptr<ir::Branch> br, std::string child_method_name, std::string contig_method_name);

  code::Stmt* transDependMultiCase(std::shared_ptr<ir::Branch> br, std::string child_method_name, std::string contig_method_name);

  // translate clear_prop()/ensure_support()/ensure_size()/ensure_cache()
  void transObjectProperty(std::shared_ptr<ir::TypeDomain> ty, std::vector<std::shared_ptr<ir::FuncDefn>>& funcs);

  /**
  * translate all queries
  */
  virtual void transAllQuery(std::vector<std::shared_ptr<ir::Query>> queries);
  void transQuery(code::FunctionDecl* fun, std::shared_ptr<ir::Query> qr, int n);

  /**
  * translate all evidences
  */
  virtual void transAllEvidence(std::vector<std::shared_ptr<ir::Evidence>> evids);

  /**
   * create FunctionDecl and setup argument for sampling algorithm
   * the function should take one argument (number of samples)
   * @return
   */
  inline SAMPLEFUN DECLARE_SAMPLEFUN();

  /**
   * translate the sampling algorithm
   * @return
   */
  virtual code::FunctionDecl* transSampleAlg();

  /**
   * create main function
   */
  virtual void createMain();

  ////////////////////////////////////////////////////////
  // Global Flag
  // Indicate the class the current expr/stmt locates in
  //    When it is not NULL, we need to register variable/distributions
  code::DeclContext* cur_context;
  // The constructor of the class pointed by cur_contex
  code::CompoundStmt* cur_constructor;
  // indicate whether using getval() or getcache()
  std::string cur_method_name;
  // indicate whether using getlikeli() or getcachelikeli()
  std::string cur_likeli_method_name;
  /////////////////////////////////////////////////////////

  /**
  * translate the blog function body to a fixed function
  */
  code::FunctionDecl* transFixedFun(std::shared_ptr<ir::FuncDefn> fd);
  /**
   * translate a clause in ir to a statement in code,
   * retvar is for return variable
   * if valuevar is given, then it will calculate weight instead of sampling
   * method denotes the method name in order to get the actual value
   */
  code::Stmt* transClause(std::shared_ptr<ir::Clause> clause,
      std::string retvar, std::string valuevar = std::string());
  /**
  * translate a Branch in ir to a statement in code,
  * retvar is for return variable
  * if valuevar is nonempty, then it will calculate weight instead of sampling
  *   >> Special Note: different translation for *Multi-Case Expr*
  */
  code::Stmt* transMultiCaseBranch(std::shared_ptr<ir::Branch> br, std::string retvar,
    std::string valuevar = std::string());
  code::Stmt* transBranch(std::shared_ptr<ir::Branch> br, std::string retvar,
    std::string valuevar = std::string());
  /**
   * translate a IfThen in ir to a statement in code,
   * retvar is for return variable
   * if valuevar is nonempty, then it will calculate weight instead of sampling
   */
  code::Stmt* transIfThen(std::shared_ptr<ir::IfThen> ith, std::string retvar,
      std::string valuevar = std::string());
  /**
   * translate an expression in ir to a statement in code,
   * retvar is for return variable
   * if valuevar is nonempty, then it will calculate weight instead of sampling
   */
  code::Expr* transExpr(std::shared_ptr<ir::Expr> expr,
    std::string valuevar = std::string());

  code::Expr* transMapExpr(std::shared_ptr<ir::MapExpr> mex);
  /**
   * translate the operation expression
   */
  code::Expr* transOprExpr(std::shared_ptr<ir::OprExpr> opr,
      std::vector<code::Expr*> args);

  /**
   * translate the array expression
   */
  code::Expr* transArrayExpr(std::shared_ptr<ir::ArrayExpr> opr,
    std::vector<code::Expr*> args);

  /**
  * translate the matrix construction expression
  */
  code::Expr* transMatrixExpr(std::shared_ptr<ir::MatrixExpr> mat);

  code::Expr* transConstSymbol(std::shared_ptr<ir::ConstSymbol> cs);

  code::Expr* transCardExpr(std::shared_ptr<ir::CardExpr> cardexp,
    std::string valuevar = std::string(),
    bool is_return_value = true);

  /**
   *  @deprecated: TODO: currently MCMC do not support origin function!
   *
   *  translate the origin function call (origin reference)
   *
   *  @param originref origin function
   *  @param valuevar variable name to hold the value (the purpose is then to calculate likelihood if non empty)
   *
   *  @return translated pointer of code::Expr
   */
  code::Expr* transOriginRefer(std::shared_ptr<ir::OriginRefer> originref, std::string valuevar =
                            std::string());
  /*
   * translate the SetExpr. Including both conditonal set and explicit set
   */
  code::Expr* transSetExpr(std::shared_ptr<ir::SetExpr> e);

  /*
   * translate the QuantForm. Including both forall and exists
   */
  code::Expr* transQuantForm(std::shared_ptr<ir::QuantForm> qt, code::Expr* cond);

  /**
   * create reference to blog function value
   */
  void addFunValueRefStmt(code::FunctionDecl* fun, std::string valuevarname,
      const std::vector<code::ParamVarDecl*>& valueindex, std::string valuerefname,
      code::Type varType = INT_REF_TYPE);

  /**
   * create assignment statement to blog function value
   */
  void addFunValueAssignStmt(code::FunctionDecl* fun, std::string valuevarname,
                             std::vector<code::ParamVarDecl*>& valueindex,
                             std::string valuerefname);

  /**
   * create a field for function value
   */
  void addFieldForFunVar(std::string varname,
      const std::vector<std::shared_ptr<ir::VarDecl> >& params,
      code::ClassDecl* cls, code::Type valueType = INT_TYPE);

  /**
   * translate the distribution expression
   * given the arguments,
   * if valuevar is nonempty, it evaluates the likelihood instead of sampling
   */
  code::Expr* transDistribution(std::shared_ptr<ir::Distribution> dist,
      std::vector<code::Expr*> args, std::string valuevar = std::string());

  /**
   * translate the function call expression
   * Note: when is_return_value == true: return a concrete value
   *                              false: return a reference to the random variable
   */
  code::Expr* transFunctionCall(std::shared_ptr<ir::FunctionCall> fc,
      std::vector<code::Expr*> args,
      bool is_return_value = true);

  code::ParamVarDecl* transParamVarDecl(code::DeclContext* context,
      const std::shared_ptr<ir::VarDecl> var);

  /**
   * given a list of Parameter variable declarations in ir, translate into a
   * vector of parameter varible declaration in code
   */
  std::vector<code::ParamVarDecl*> transParamVarDecls(
      code::DeclContext* context, std::shared_ptr<ir::FuncDefn> fun);
};

} /* namespace codegen */
} /* namespace swift */

