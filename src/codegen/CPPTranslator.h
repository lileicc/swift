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

namespace swift {
namespace codegen {

class CPPTranslator {
public:
  CPPTranslator();
  virtual ~CPPTranslator();
  void translate(swift::ir::BlogModel* model);
  code::Code* getResult() const;

private:
  code::Code* prog; // holder for result target code
  code::ClassDecl* coreCls; // main Class for the sampler;
  code::NamespaceDecl* coreNs; // main namespace
  code::FunctionDecl* coreClsInit; // init function for main class
  void transTypeDomain(std::shared_ptr<ir::TypeDomain> td);
  void transFun(std::shared_ptr<ir::FuncDefn> fd);
  void transFunBody(code::FunctionDecl* fun, std::shared_ptr<ir::Clause> clause,
      std::string valuevarname, std::string markvarname);
  code::Stmt* transClause(std::shared_ptr<ir::Clause> clause,
      std::string retvar);
  code::Stmt* transBranch(std::shared_ptr<ir::Branch> br, std::string retvar);
  code::Stmt* transIfThen(std::shared_ptr<ir::IfThen> ith, std::string retvar);
  code::Expr* transExpr(std::shared_ptr<ir::Expr> expr);
  /**
   * translate the distribution expression
   * given the arguments
   */
  code::Expr* transDistribution(std::shared_ptr<ir::Distribution> dist,
      std::vector<code::Expr*> args);
  code::ParamVarDecl* transParamVarDecl(code::DeclContext* context,
      const std::shared_ptr<ir::VarDecl> var);
  std::vector<code::ParamVarDecl*> transParamVarDecls(
      code::DeclContext* context,
      const std::vector<std::shared_ptr<ir::VarDecl> > & vars);

  static code::Type mapIRTypeToCodeType(const ir::Ty * ty); // map ir type to code type

  static const code::Type INT_TYPE;

  static const code::Type INT_REF_TYPE;

  static const code::Type DOUBLE_TYPE;

  static const code::Type STRING_TYPE;

  static const code::Type BOOL_TYPE;

  /**
   * field name inside class for declared type
   */
  static const std::string DISTINCT_FIELDNAME;

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


  /**
   * initial value set to mark_var (default -1)
   */
  static const int INIT_SAMPLE_NUM;

  /**
   * name of variable for current_loop or current sample num
   */
  static const std::string CURRENT_SAMPLE_NUM_VARNAME;

  /**
   * name for the return variable;
   */
  static const std::string RETURN_VAR_NAME;

  /**
   * name for the mark variable, which is refering the mark var
   * associated with this one;
   */
  static const std::string MARK_VAR_REF_NAME;

};

} /* namespace codegen */
} /* namespace swift */

