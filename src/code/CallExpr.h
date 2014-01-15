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

class CallExpr: public Expr {
public:
  CallExpr(Expr* fn, std::vector<Expr*> args = std::vector<Expr *>());
  ~CallExpr();

  Expr* getFunc();
  std::vector<Expr*>& getArgs();

  // For Printer
  void print(printer::Printer* prt);
private:
  Expr* fn;
  std::vector<Expr*> args;
};

} /* namespace code */
} /* namespace swift */
