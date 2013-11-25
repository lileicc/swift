/*
 * CPPTranslator.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CPPTranslator.h"

namespace swift {
namespace codegen {

const code::QualType CPPTranslator::INT_TYPE("int");
const code::QualType CPPTranslator::DOUBLE_TYPE("double");
const code::QualType CPPTranslator::STRING_TYPE("std::string");
const code::QualType CPPTranslator::BOOL_TYPE("bool");
const std::string CPPTranslator::DISTINCT_FIELDNAME = "__name_";
const int CPPTranslator::INIT_SAMPLE_NUM = -1;

namespace {
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
 * return the variable name to get the number of samples for the current variable
 */
std::string getMarkVarName(std::string name) {
  return "__mark_" + name;
}

}

CPPTranslator::CPPTranslator() {
  // TODO Auto-generated constructor stub

}

CPPTranslator::~CPPTranslator() {
  // TODO Auto-generated destructor stub
}

void CPPTranslator::translate(swift::ir::BlogModel* model) {
  for (auto ty : model->getTypes())
    transTypeDomain(ty);
  for (auto fun : model->getRandFuncs())
    transFun(fun);
}

code::Code* CPPTranslator::getResult() const {
  return prog;
}

void CPPTranslator::transTypeDomain(std::shared_ptr<ir::TypeDomain> td) {
  const std::string& name = td->getName();
  code::ClassDecl* cd = code::ClassDecl::createClassDecl(coreNs, name);
  code::FieldDecl::createFieldDecl(cd, DISTINCT_FIELDNAME, STRING_TYPE);
  int len = td->getPreLen();
  std::string numvar = getVarOfNumType(name);
  // create a field in the main class:::    int numvar;
  code::FieldDecl* fd = code::FieldDecl::createFieldDecl(coreCls, numvar,
      INT_TYPE);
  // create a field in the main class:::    int mark_numvar;
  std::string marknumvar = getMarkVarName(numvar);
  fd = code::FieldDecl::createFieldDecl(coreCls, marknumvar, INT_TYPE);
  // add in the init function:::            numvar = len;
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::VarRef(numvar),
          new code::IntegerLiteral(len), code::OpKind::BO_ASSIGN));
  // add in the init function:::            mark_numvar = -1;
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::VarRef(marknumvar),
          new code::IntegerLiteral(INIT_SAMPLE_NUM), code::OpKind::BO_ASSIGN));
  if (len > 0) {
    // create the function for getting number of objects in this instance, i.e. numvar
    code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(coreCls,
        getGetterFunName(numvar), INT_TYPE, true);
    fun->addStmt(new code::ReturnStmt(new code::VarRef(numvar)));
    // TODO please add the corresponding distinct name

  }
  // handle number statement
  int numstlen = td->getNumberStmtSize();
  if (numstlen > 0) {
    // TODO create functions for number statement and their likelihood

  }
}

void CPPTranslator::transFun(std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string getterfunname = getGetterFunName(name);
  code::QualType retty = mapIRTypeToCodeType(fd->getRetTyp());
  // translate random function
  // create gettfunname function
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(coreCls,
      getterfunname, retty);
  fun->setParams(transParamVarDecls(fun, fd->getArgs()));
  if (fd->isRand()) {
    //
    // TODO translate body
    // fun->addStmt(transClause(fd->getBody()));

    // TODO add likelihood function
    std::string likelifunname = getLikeliFunName(name);
    code::FunctionDecl* likelifun = code::FunctionDecl::createFunctionDecl(
        coreCls, likelifunname, DOUBLE_TYPE);
    fun->setParams(transParamVarDecls(fun, fd->getArgs()));
    // add the likelihood calculation
//    fun->addStmt(transClause(fd->getBody()));

  }
}

code::Stmt* CPPTranslator::transClause(std::shared_ptr<ir::Clause> clause,
    std::string retvar) {
  std::shared_ptr<ir::Branch> br = std::dynamic_pointer_cast<ir::Branch>(
      clause);
  if (br) {
    return transBranch(br, retvar);
  }
  std::shared_ptr<ir::IfThen> ith = std::dynamic_pointer_cast<ir::IfThen>(
      clause);
  if (ith) {
    return transIfThen(ith, retvar);
  }
  std::shared_ptr<ir::Expr> expr = std::dynamic_pointer_cast<ir::Expr>(clause);
  if (expr) {
    code::CompoundStmt* cst = new code::CompoundStmt();
    cst->addStmt(
        new code::BinaryOperator(new code::VarRef(retvar), transExpr(expr),
            code::OpKind::BO_ASSIGN));
    // TODO no 100% correct here
    return cst;
  }
}

code::ParamVarDecl* CPPTranslator::transParamVarDecl(code::DeclContext* context,
    const std::shared_ptr<ir::VarDecl> var) {
  return new code::ParamVarDecl(context, var->getVar(),
      mapIRTypeToCodeType(var->getTyp()));
}

std::vector<code::ParamVarDecl*> CPPTranslator::transParamVarDecls(
    code::DeclContext* context,
    const std::vector<std::shared_ptr<ir::VarDecl> > & vars) {
  std::vector<code::ParamVarDecl*> vds;
  for (auto v : vars) {
    vds.push_back(transParamVarDecl(context, v));
  }
  return vds;
}

code::Stmt* CPPTranslator::transBranch(std::shared_ptr<ir::Branch> br,
    std::string retvar) {
  code::SwitchStmt* sst = new code::SwitchStmt(transExpr(br->getVar()));
  code::CaseStmt* cst;
  for (int i = 0; i < br->size(); i++) {
    cst = new code::CaseStmt(transExpr(br->getCond(i)),
        transClause(br->getBranch(i), retvar));
    sst->addStmt(cst);
    sst->addStmt(new code::BreakStmt());
  }
  return sst;
}

code::Stmt* CPPTranslator::transIfThen(std::shared_ptr<ir::IfThen> ith,
    std::string retvar) {
  // TODO translate ifthenelse
}

code::Expr* CPPTranslator::transExpr(std::shared_ptr<ir::Expr> expr) {
  // TODO translate expression
}

code::QualType CPPTranslator::mapIRTypeToCodeType(const ir::Ty* ty) {
  switch (ty->getTyp()) {
  case ir::IRConstant::BOOL:
    return BOOL_TYPE;
  case ir::IRConstant::INT:
    return INT_TYPE;
  case ir::IRConstant::DOUBLE:
    return DOUBLE_TYPE;
  case ir::IRConstant::STRING:
    return STRING_TYPE;
  default:
    return INT_TYPE; // all declared type return int type
  }
}

} /* namespace codegen */
} /* namespace swift */

