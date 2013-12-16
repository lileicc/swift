/*
 * CallExpr.h
 *
 *  Created on: Nov 26, 2013
 *      Author: leili
 */

#pragma once
#include <vector>
#include "Expr.h"

namespace swift {
namespace code {

class CallExpr: public swift::code::Expr {
public:
  CallExpr(Expr* fn, std::vector<Expr*> args);
  CallExpr(Expr* fn);
  ~CallExpr();

  // For Printer
  void print(printer::CPPPrinter* prt);
private:
  Expr* fn;
  std::vector<Expr*> args;
};

} /* namespace code */
} /* namespace swift */
