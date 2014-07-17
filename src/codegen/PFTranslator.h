/*
 * PFTranslator.h
 *
 *  Created on: Jul 14, 2014
 *      Author: yiwu
 */

#pragma once

#include "Translator.h"

namespace swift {
namespace codegen {

class PFTranslator: public swift::codegen::Translator {
public:
  PFTranslator();
  void translate(swift::ir::BlogModel* model);
  code::Code* getResult();
  
protected:
  /**
  * how many particles to sample in total : default parameter for PF
  */
  static const int TOTAL_NUM_PARTICLES;

  // Time Series Features
  int ModelDependency;
  int ModelTimeLimit;

  // classes for memorization for static and temporal data
  STATE coreStaticCls; // memorization data structure for static variables
  static const std::string StaticClsName;
  code::FunctionDecl* coreStaticClsInit; // clear function for static varaibles
  STATE coreTemporalCls; // memorization data structure for temporal variables
  code::FunctionDecl* coreTemporalClsInit; // init function for temporal varaibles
  code::FunctionDecl* coreTemporalClsClear; // clear function for temporal varaibles
  static const std::string MAIN_CLEAR_FUN_NAME;
  static const std::string TemporalClsName;
  
  //Constant Variable Names of Parameters of Particle Filtering
  static const std::string TIMESTEP_LIMIT_VAR_NAME; // variable for Maximum TimeStep
  static const std::string PARTICLE_NUM_VAR_NAME; // variable for Number of Particles
  static const std::string DEPEND_NUM_VAE_NAME; // variable for dependency
  
  // Internal Varaibles for Memorization Particles
  static const std::string STAT_MEMO_VAR_NAME;
  static const std::string TEMP_MEMO_VAR_NAME;
  static const std::string PTR_STAT_MEMO_VAR_NAME;
  static const std::string PTR_TEMP_MEMO_VAR_NAME;
  static const std::string PTR_BACKUP_VAR_NAME;

  // Types for Memorization Data Structure
  static const TYPE STAT_MEMO_TYPE;
  static const TYPE REF_STAT_MEMO_TYPE;
  static const TYPE PTR_STAT_MEMO_TYPE;
  static const TYPE TEMP_MEMO_TYPE;
  static const TYPE REF_TEMP_MEMO_TYPE;
  static const TYPE PTR_TEMP_MEMO_TYPE;

  // Variable Name denoting data structure containing all the required info
  static const std::string CUR_STATE_VAR_NAME;
  static const std::string CUR_TIMESTEP_VAR_NAME;

  // Temperary Variable Name
  static const std::string TMP_LOOP_VAR_NAME;
  static const std::string TMP_LOCAL_TS_INDEX_VAR_NAME;

  // Util Functions for Particle Filtering in Util.h
  static const std::string PF_RESAMPLE_FUN_NAME;
  static const std::string PF_COPY_PTR_FUN_NAME;

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
   */
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
  void transEvidence(code::CompoundStmt* fun,
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
  void transQuery(code::CompoundStmt* cmp, std::shared_ptr<ir::Query> qr,
      int n);
  /**
   * create reference to blog function value
   */
  void addFunValueRefStmt(code::FunctionDecl* fun, std::string valuevarname,
      std::vector<code::ParamVarDecl*>& valueindex, std::string valuerefname,
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
};

} /* namespace codegen */
} /* namespace swift */

