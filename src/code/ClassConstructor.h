/*
 * ClassConstructor.h
 *
 *  Created on: Jan 16, 2014
 *      Author: leili
 */

#pragma once
#include "ClassDecl.h"
#include "Type.h"
#include "FunctionDecl.h"

namespace swift {
namespace code {

class ClassConstructor: public swift::code::FunctionDecl {
public:
  virtual ~ClassConstructor();
  static ClassConstructor* createClassConstructor(ClassDecl * cls,
      std::vector<ParamVarDecl*> params = std::vector<ParamVarDecl*>());
  void print(printer::Printer* prt);
protected:
  ClassConstructor(ClassDecl * cls, Type ty);
};

} /* namespace code */
} /* namespace swift */
