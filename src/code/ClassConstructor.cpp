/*
 * ClassConstructor.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: leili
 */

#include "ClassConstructor.h"

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
    FunctionDecl(cls, cls->getName(), ty, false) {
}

} /* namespace code */
} /* namespace swift */
