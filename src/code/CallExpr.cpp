/*
 * CallExpr.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: leili
 */

#include "CallExpr.h"

namespace swift {
namespace code {

CallExpr::CallExpr(code::Expr* fn, std::vector<code::Expr*> args) :
    fn(fn), args(args) {
}


CallExpr::~CallExpr() {
  delete fn;
  for (auto a : args)
    delete a;
  args.clear();
}

code::Expr* CallExpr::getFunc() {
  return fn;
}

std::vector<code::Expr*>& CallExpr::getArgs() {
  return args;
}

// For Printer
void CallExpr::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
