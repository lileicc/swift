/*
 * ClassConstructor.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: leili
 */

#include "ClassConstructor.h"
#include "BinaryOperator.h"
#include "CallExpr.h"
#include "Identifier.h"

namespace swift {
namespace code {

ClassConstructor::~ClassConstructor() {
  if (initExpr != NULL) delete initExpr;
}

ClassConstructor* ClassConstructor::createClassConstructor(ClassDecl* cls,
    std::vector<ParamVarDecl*> params) {
  ClassConstructor* cc = new ClassConstructor(cls, Type(cls->getName()));
  cc->setParams(params);
  cls->addDecl(cc);
  return cc;
}

void ClassConstructor::print(printer::Printer* prt) {
  prt->print(this);
}

ClassConstructor::ClassConstructor(ClassDecl* cls, Type ty) :
    FunctionDecl(cls, cls->getName(), ty, false), initExpr(NULL) {
}

void ClassConstructor::addInitExpr(Expr* initExpr) {
  if (this->initExpr) {
    this->initExpr = new BinaryOperator(this->initExpr, initExpr,
        OpKind::BO_COMMA);
  } else
    this->initExpr = initExpr;
}

void ClassConstructor::addInitExpr(std::string varName, Expr* expr) {
  if (expr == NULL)
    addInitExpr(new code::CallExpr(new Identifier(varName)));
  else
    addInitExpr(new code::CallExpr(new Identifier(varName), std::vector<Expr*>{expr}));
}

void ClassConstructor::addInitExpr(std::string varName, std::vector<Expr*> expr) {
  addInitExpr(new code::CallExpr(new Identifier(varName), expr));
}

Expr* ClassConstructor::getInitExpr() {
  return initExpr;
}

} /* namespace code */
} /* namespace swift */
