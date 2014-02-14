/*
 * CPPTranslator.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
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

class CPPTranslator {
public:
  CPPTranslator();
  virtual ~CPPTranslator();
  void translate(swift::ir::BlogModel* model);
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

private:
  code::Code* prog; // holder for result target code
  bool useTag;
  code::ClassDecl* coreCls; // main Class for the sampler;
  code::NamespaceDecl* coreNs; // main namespace
  code::FunctionDecl* coreClsConstructor; // construction function for main class
  code::FunctionDecl* coreClsInit; // init function for main class

  code::FunctionDecl* coreClsDebug; // debug function for main class
  static const std::string MAIN_DEBUG_METHOD_NAME;
  // a map from function name (in target code) to FunctionDecl*
  std::map<std::string, code::FunctionDecl*> declared_funs;

  code::FunctionDecl* mainFun; //main function
  code::FunctionDecl* coreClsPrint; // print function for answers
  code::FunctionDecl* transSampleAlg();

  void transTypeDomain(std::shared_ptr<ir::TypeDomain> td);
  /**
   * translate blog function
   */
  void transFun(std::shared_ptr<ir::FuncDefn> fd);

  /**
   * create declaration of variables/fields
   * initialization statements
   */
  void createInit();

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

  code::Expr* transConstSymbol(std::shared_ptr<ir::ConstSymbol> cs);

  code::Expr* transCardExpr(std::shared_ptr<ir::CardExpr> cardexp);

  /*
   * translate the SetExpr. Including both conditonal set and explicit set
   */
  code::Expr* transSetExpr(std::shared_ptr<ir::SetExpr> e);

  /**
   * translate the evidence in obs statement, the resulting statement is added
   * to the declaration context
   */
  void transEvidence(code::FunctionDecl* context,
      std::shared_ptr<ir::Evidence> evid);

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

  static code::Type mapIRTypeToCodeType(const ir::Ty * ty, bool isRef = false); // map ir type to code type

  static const code::Type INT_TYPE;
  static const code::Type INT_VECTOR_TYPE;
  static const code::Type INT_REF_TYPE;

  static const code::Type DOUBLE_TYPE;
  static const code::Type DOUBLE_VECTOR_TYPE;

  static const code::Type STRING_TYPE;

  static const code::Type BOOL_TYPE;

  static const code::Type VOID_TYPE;

  static const code::Type MAP_BASE_TYPE;

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
};

} /* namespace codegen */
} /* namespace swift */

