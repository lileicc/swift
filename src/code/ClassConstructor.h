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

#include <string>
#include <vector>

namespace swift {
namespace code {

class ClassConstructor: public swift::code::FunctionDecl {
public:
  virtual ~ClassConstructor();
  static ClassConstructor* createClassConstructor(ClassDecl * cls,
      std::vector<ParamVarDecl*> params = std::vector<ParamVarDecl*>());
  void addInitExpr(Expr* initExpr);
  void addInitExpr(std::string varName, Expr* expr = NULL);
  void addInitExpr(std::string varName, std::vector<Expr*> expr);
  void print(printer::Printer* prt);
  Expr* getInitExpr();
protected:
  ClassConstructor(ClassDecl * cls, Type ty);
private:
  Expr* initExpr;
};

} /* namespace code */
} /* namespace swift */
