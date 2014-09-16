/*
 * Translator.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../ir/IRHeader.h"
#include "../code/Code.h"
#include "../util/Configuration.h"

namespace swift {
namespace codegen {

/**
 * the following macro are defining construction of language elements in BLOG
 */
typedef code::ClassDecl* TYPEDEFN;
typedef code::Type TYPE;
typedef code::FieldDecl* ORIGINDEFN;
typedef code::Expr* EXPR;
typedef code::Stmt* STMT;
typedef code::FunctionDecl* SAMPLEFUN;
typedef code::ClassDecl* STATE; // state (partial possible world)
typedef code::VarDecl* SITE; // storage site declaration

class Translator {
public:
  Translator();
  virtual ~Translator();
  virtual void translate(swift::ir::BlogModel* model);
  code::Code* getResult();

protected:

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
  inline STMT CREATE_INSTANCE(std::string tyname, std::string instname, std::vector<EXPR> originvalues = std::vector<EXPR>(), EXPR ncopy = nullptr);
  
  inline EXPR ACCESS_ORIGIN_FIELD(std::string tyname, std::string originname, EXPR originarg);

  /**
   * create FunctionDecl and setup argument for sampling algorithm
   * the function should take one argument (number of samples)
   * @return
   */
  inline SAMPLEFUN DECLARE_SAMPLEFUN();
  
  inline SITE DECLARE_STORE_SITE();

  code::Code* prog; // holder for result target code
  bool useTag;
  STATE coreCls; // main Class for the sampler;
  code::NamespaceDecl* coreNs; // main namespace
  code::FunctionDecl* coreClsConstructor; // construction function for main class
  code::FunctionDecl* coreClsInit; // init function for main class

  code::FunctionDecl* coreClsDebug; // debug function for main class
  static const std::string MAIN_DEBUG_METHOD_NAME;
  // a map from function name (in target code) to FunctionDecl*
  std::map<std::string, code::FunctionDecl*> declared_funs;

  code::FunctionDecl* mainFun; //main function
  code::FunctionDecl* coreClsPrint; // print function for answers

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
  static const std::string MAIN_FUN_NAME;
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
  void transEvidence(code::FunctionDecl* context,
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
  void transQuery(code::FunctionDecl* fun, std::shared_ptr<ir::Query> qr,
      int n);
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
      code::Type valueType = INT_TYPE);

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
      code::DeclContext* context,
      const std::vector<std::shared_ptr<ir::VarDecl> > & vars);

  static code::Type mapIRTypeToCodeType(const ir::Ty * ty, bool isRef = false, bool isPtr = false); // map ir type to code type

  static const code::Type INT_TYPE;
  static const code::Type INT_VECTOR_TYPE;
  static const code::Type INT_REF_TYPE;
  static const code::Type INT_CONST_TYPE; // this is to define global constant values

  static const code::Type DOUBLE_TYPE;
  static const code::Type DOUBLE_REF_TYPE;
  static const code::Type DOUBLE_VECTOR_TYPE;

  static const code::Type STRING_TYPE;

  static const code::Type TIMESTEP_TYPE;

  static const code::Type BOOL_TYPE;

  static const code::Type VOID_TYPE;

  static const code::Type MATRIX_TYPE;
  static const code::Type MATRIX_REF_TYPE;
  static const code::Type MATRIX_CONST_TYPE;
  static const code::Type MATRIX_ROW_VECTOR_TYPE;
  static const code::Type MATRIX_COL_VECTOR_TYPE;
  static const code::Type MATRIX_CONTAINER_TYPE;

  static const code::Type ARRAY_BASE_TYPE;

  static const code::Type MAP_BASE_TYPE;

  static const code::Type SET_BASE_TYPE;

  static const std::string SAMPLER_VAR_NAME;

  static const std::string MAIN_SAMPLING_FUN_NAME;

  static const std::string MAIN_NAMESPACE_NAME;

  static const std::string MAIN_INIT_FUN_NAME;
  /**
   * field name inside class for declared type
   */
  static const std::string DISTINCT_FIELDNAME;

  /**
   * function name for set evidence
   */
  static const std::string SET_EVIDENCE_FUN_NAME;

  /**
   * function name for query evaluation
   */
  static const std::string QUERY_EVALUATE_FUN_NAME;

  /**
   * variable name prefix for holding the answer for a query
   */
  static const std::string ANSWER_VAR_NAME_PREFIX;

  //number of samples, argument for init() and sample()
  static const std::string LOCAL_NUM_SAMPLE_ARG_NAME;

  /**
   * class name for processing query answer (Using historgram)
   */
  static const std::string HISTOGRAM_CLASS_NAME;

  /**
   * function name for processing query answer
   */
  static const std::string HISTOGRAM_ADD_METHOD_NAME;

  /**
   * function name for processing query answer
   */
  static const std::string HISTOGRAM_PRINT_METHOD_NAME;

  // function name for compute log(a == b)
  static const std::string LOG_EQUAL_FUN_NAME;

  // function name for checking whether a number is finite
  static const std::string ISFINITE_FUN_NAME;

  // MACRO name for holding negative INFINITE
  static const std::string NEG_INFINITE_NAME;

  /**
   * function name for printing query answer
   */
  static const std::string ANSWER_PRINT_METHOD_NAME;

  /**
   * function name for the distribution init
   */
  static const std::string DISTRIBUTION_INIT_FUN_NAME;

  /**
   * function name for the distribution gennerating a sample
   */
  static const std::string DISTRIBUTION_GEN_FUN_NAME;

  /**
   * function name for the distribution calculating the likelihood of a sample
   */
  static const std::string DISTRIBUTION_LIKELI_FUN_NAME;

  /**
   * function name for the distribution calculating the log-likelihood of a sample
   */
  static const std::string DISTRIBUTION_LOGLIKELI_FUN_NAME;

  // name of the uniform int distribution, i.e. UniformInt
  static const std::string UNIFORM_INT_DISTRIBUTION_NAME;

  // name of the uniformchoice distribution, i.e. UniformChoice
  static const std::string UNIFORM_CHOICE_DISTRIBUTION_NAME;

  // function name for generating a full set: _gen_full() in util.h
  static const std::string GEN_FULL_SET_NAME;

  // function name for internal apply: _apply() in util.h
  static const std::string APPLY_FUNC_NAME;

  // function name for internal filter: _filer() in util.h
  static const std::string FILTER_FUNC_NAME;

  // function name for internal filter with range input: _filer() in util.h
  static const std::string FILTER_RANGE_FUNC_NAME;

  // function name for internal filter counter: _count() in util.h
  static const std::string FILTER_COUNT_NAME;

  // function name for internal filter counter with range input: std::count() in <algorithm>
  static const std::string FILTER_RANGE_COUNT_NAME;

  // function name for internal forall operator: _forall() in util.h
  static const std::string FORALL_NAME;

  // function name for internal forall operator with range input: std::all_of() in <algorithm>
  static const std::string FORALL_RANGE_NAME;

  // function name for internal exists operator: _exists() in util.h
  static const std::string EXISTS_NAME;

  // function name for internal exists operator with range input: std::any_of() in <algorithm>
  static const std::string EXISTS_RANGE_NAME;

  // Builtin Functions for Matrix Initialization
  static const std::string TO_MATRIX_FUN_NAME;

  /**
   * method name for vector.resize()
   */
  static const std::string VECTOR_RESIZE_METHOD_NAME;
  /**
   * method name for vector.push_back()
   */
  static const std::string VECTOR_ADD_METHOD_NAME;
  /**
   * method name for append()
   */
  static const std::string APPEND_FUN_NAME;
  /**
   * class name for vector
   */
  static const std::string VECTOR_CLASS_NAME;
  /**
   * class name for DynamicTable
   */
  static const std::string DYNAMICTABLE_CLASS_NAME;
  /**
   * method name for DynamicTable.resize()
   */
  static const std::string DYNAMICTABLE_RESIZE_METHOD_NAME;
  /**
   * initial value set to mark_var (default 1)
   */
  static const int INIT_SAMPLE_NUM;

  // value for null
  static const int NULLSYMBOL_VALUE;

  /**
   * how many samples to take in total
   */
  static const int TOTAL_NUM_SAMPLES;

  /**
   * name of variable for current_loop or current sample num
   */
  static const std::string CURRENT_SAMPLE_NUM_VARNAME;

  /**
   * name for the global variable holding weight of each possible world
   */
  static const std::string GLOBAL_WEIGHT_VARNAME;

  /**
   * name for the local variable holding likelihood weight;
   */
  static const std::string WEIGHT_VAR_REF_NAME;

  /**
   * name for the local variable holding FuncAppVar
   */
  static const std::string VALUE_VAR_REF_NAME;

  /**
   * name for the argument holding FuncAppVar value
   */
  static const std::string VALUE_ARG_NAME;

  /**
   * name for the mark variable, which is refering the mark var
   * associated with this one;
   */
  static const std::string MARK_VAR_REF_NAME;

  /**
   * string name for the random device
   */
  static const std::string RANDOM_DEVICE_VAR_NAME;

  /**
   * string name for the random engine, note a random engine need to use random device as an input source of randomness
   */
  static const std::string RANDOM_ENGINE_VAR_NAME;

  /**
   * function name for fill_n (="fill_n");
   */
  static const std::string FILL_N_FUN_NAME;

  /**
   * type for the random engine
   */
  static const code::Type RANDOM_ENGINE_TYPE;

  static bool COMPUTE_LIKELIHOOD_IN_LOG;

  static swift::Configuration* config;

  /**
* give the name of the type,
* return the variable name corresponding to the number of objects for this type
*/
std::string getVarOfNumType(std::string name) {
  return "__num_" + name;
}

/**
* given the name of a variable (can be number var, or random function)
* return the function name to get the number of objects for this type
*/
std::string getGetterFunName(std::string name) {
  return "__get_" + name;
}

/**
* given the name of a variable (can be number var, or random function)
* return the function name to get the likelihood of objects for this type
*/
std::string getLikeliFunName(std::string name) {
  return "__likeli_" + name;
}

/**
* given the name of a variable (can be number var, or random function)
* return the function name to set the value
*/
std::string getSetterFunName(std::string name) {
  return "__set_" + name;
}

/**
* given the name of a variable (can be number var, or random function)
* return the function name to set the value
*/
std::string getEnsureFunName(std::string name) {
  return "__ensure_" + name;
}

/**
* given the name of a fixed function
* return the function name  assigned in the translated program
*/
std::string getFixedFunName(std::string name) {
  return "__fixed_" + name;
}

/**
* given the name of a variable (can be number var, or random function)
* return the variable name to get the number of samples for the current variable
*/
std::string getMarkVarName(std::string name) {
  return "__mark_" + name;
}

/**
* given the name of a variable (can be number var, or random function)
* return the variable name to get the value of that var/fun
*/
std::string getValueVarName(std::string name) {
  return "__value_" + name;
}

/**
* given the type name,
* return the variable name to store all the instances in that type
*/
std::string getInstanceArrayName(std::string name) {
  return "__instance_" + name;
}

};

} /* namespace codegen */
} /* namespace swift */

