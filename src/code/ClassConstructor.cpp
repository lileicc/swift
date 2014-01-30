/*
 * ClassConstructor.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: leili
 */

#include "ClassConstructor.h"
#include "BinaryOperator.h"

namespace swift {
namespace code {

ClassConstructor::~ClassConstructor() {
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
    FunctionDecl(cls, cls->getName(), ty, false), initExpr(nullptr) {
}

void ClassConstructor::addInitExpr(Expr* initExpr) {
  if (this->initExpr) {
    this->initExpr = new BinaryOperator(this->initExpr, initExpr, OpKind::BO_COMMA);
  } else
    this->initExpr = initExpr;
}

} /* namespace code */
} /* namespace swift */
