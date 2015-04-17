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

namespace swift {
namespace codegen {

class MHTranslator: public swift::codegen::Translator {
public:
  MHTranslator();
  void translate(std::shared_ptr<swift::ir::BlogModel> model);
  code::Code* getResult();
  void setIterationNum(int iter);
  void setBurnInNum(int iter);
  
protected:
  /**
  * how many interations to sample in total : default parameter for MCMC
  */
  static const int DEFAULT_TOTAL_NUM_ITERATIONS;
  int iterNum;
  int burnInNum; // by defualt: burnIn = iterNum/2

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
  static const std::string MCMC_Global_GetValNumVar_MethodName;
  static const std::string MCMC_Global_GetCacheNumVar_MethodName;
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
  static const std::string MCMC_PropSize_VarName;
  static const std::string MCMC_Capacity_VarName;

  // Temp variable
  static const std::string TEMP_N_NAME;
  static const std::string TEMP_FROM_NAME;
  static const std::string TEMP_TO_NAME;
  static const std::string TEMP_IND_NAME;
  static const std::string TEMP_VAL_NAME;

  // Util Func Name
  static const std::string UtilSetEviFuncName;
  static const std::string UtilUpdateRefFuncName;
  static const std::string UtilClearRefFuncName;
  static const std::string UtilCalcRefDiffFuncName;
  static const std::string UtilFreeObjFuncName;



  ////////// @Start ///////////////////////
  // Start from Here!!!!
  ///////////////////////////////////////////////////////////////////

  /**
   * declare a named type
   * it will create class definition for this type, and one field "name" (std::string)
   */
  inline TYPEDEFN DECLARE_TYPE(std::string name);

  inline ORIGINDEFN DECLARE_ORIGIN_FIELD(TYPEDEFN typedf, std::string originname,
      TYPE origintype);
  /**
   *  create BLOG instance, which can be distinct symbols, 
   *  or instance generated in possible worlds
   *
   *  @param tyname         blog type name
   *  @param instname       instance name
   *  @param originvalues   a vector of values for origin fields
   *  @param ncopy          how many copy to create, if null, it will just create 1
   *
   *  @return an assignment statement in target code
   */
  inline STMT CREATE_INSTANCE(std::string tyname, std::string instname, std::vector<EXPR> originvalues = std::vector<EXPR>(), EXPR ncopy = nullptr, bool inGetter = false);
  
  inline EXPR ACCESS_ORIGIN_FIELD(std::string tyname, std::string originname, EXPR originarg);

  /**
   * create FunctionDecl and setup argument for sampling algorithm
   * the function should take one argument (number of samples)
   * @return
   */
  inline SAMPLEFUN DECLARE_SAMPLEFUN();
  
  inline SITE DECLARE_STORE_SITE();

  /**
   * translate the sampling algorithm
   * @return
   */
  virtual code::FunctionDecl* transSampleAlg();

  void transTypeDomain(std::shared_ptr<ir::TypeDomain> td);
  /**
   * translate blog function
   */
  void transFun(std::shared_ptr<ir::FuncDefn> fd);

  /**
   * create declaration of variables/fields
   * initialization statements
   */
  virtual void createInit();

  /**
   * create main function
   */
  void createMain();
  
  /**
   * translate the blog function to getter function
   * ::: random Color truecolor(Ball b) => int get_truecolor(int i)
   */
  code::FunctionDecl* transGetterFun(std::shared_ptr<ir::FuncDefn> fd);
  /**
   * translate the blog function body to likelihood function
   */
  code::FunctionDecl* transLikeliFun(std::shared_ptr<ir::FuncDefn> fd);
  /**
   * setup the Setter function for a predicate
   * will set a value for the given Function Application variable
   * and calculate the likelihood (need to call the likelifun)
   */
  code::FunctionDecl* transSetterFun(std::shared_ptr<ir::FuncDefn> fd);
  /**
  * translate the blog function body to a fixed function
  */
  code::FunctionDecl* transFixedFun(std::shared_ptr<ir::FuncDefn> fd);
  /**
   * translate a clause in ir to a statement in code,
   * retvar is for return variable
   * if valuevar is given, then it will calculate weight instead of sampling
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
  code::Expr* transExpr(std::shared_ptr<ir::Expr> expr, std::string valuevar =
      std::string());

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

  code::Expr* transCardExpr(std::shared_ptr<ir::CardExpr> cardexp, std::string valuevar =
                            std::string());
  
  /**
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
   * translate the evidence in obs statement, the resulting statement is added
   * to the declaration context
   *
   *  @param context within which the translated statment will reside
   *  @param evid    ir evidence declaration
   */
  void transEvidence(std::vector<std::vector<code::Stmt*> >&setterFuncs,
      std::vector<std::vector<code::Stmt*> >&likeliFuncs,
      std::shared_ptr<ir::Evidence> evid, bool transFuncApp = true);

  /**
   * translate all evidences
   */
  void transAllEvidence(std::vector<std::shared_ptr<ir::Evidence>> evids);

  /**
   * translate all queries
   */
  void transAllQuery(std::vector<std::shared_ptr<ir::Query>> queries);
  /**
   * translate n-th query
   */
  void transQuery(std::vector<std::vector<code::Stmt*> >& queryFuncs,
      std::vector<std::vector<code::Stmt*> >& printFuncs, 
      std::shared_ptr<ir::Query> qr, int n);
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
   */
  code::Expr* transFunctionCall(std::shared_ptr<ir::FunctionCall> fc,
      std::vector<code::Expr*> args);

  code::ParamVarDecl* transParamVarDecl(code::DeclContext* context,
      const std::shared_ptr<ir::VarDecl> var);

  /**
   * given a list of Parameter variable declarations in ir, translate into a
   * vector of parameter varible declaration in code
   */
  std::vector<code::ParamVarDecl*> transParamVarDecls(
      code::DeclContext* context, std::shared_ptr<ir::FuncDefn> fun);

  // Util Functions
  static code::Stmt* referStaticStateStmt(code::DeclContext* context);
  static code::Stmt* referTempStateStmt(code::DeclContext* context, std::string tempVar);
  static code::Expr* referVarFromState(code::Expr*);
  static code::ForStmt* createForeachLoop(std::string loop_var, std::string loop_n, code::Stmt* body = NULL, 
      bool isVarDefined = false, bool isLess = true);
  static code::Expr* createVarPlusDetExpr(std::string varName, int det = 0);
  static bool isTemporalType(code::Type ty);
  static code::Expr* tempTableEntryRefer(std::string table, int ts = -1);

  // Utils for Liu-West Filter
  // Record all the random function names accociated with at least *ONE* observation
  static std::set<std::string> obsFuncStore;
  static const std::string DOUBLE_PERTURB_FUN_NAME;
  static const std::string MATRIX_PERTURB_FUN_NAME;
};

} /* namespace codegen */
} /* namespace swift */

