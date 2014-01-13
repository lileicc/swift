/*
 * NewExpr.h
 *
 *  Created on: Jan 13, 2014
 *      Author: leili
 */

#pragma once

#include "Expr.h"
#include "Type.h"

namespace swift {
namespace code {

class NewExpr: public swift::code::Expr {
public:
  NewExpr(Expr * expr);
  NewExpr(Type ty, Expr* size);
  virtual ~NewExpr();
  void print(printer::Printer* prt);
private:
  Type ty;
  Expr* expr;
  bool isArray;
};

} /* namespace code */
} /* namespace swift */
