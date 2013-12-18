/*
 * CallExpr.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: leili
 */

#include "CallExpr.h"

namespace swift {
namespace code {

CallExpr::CallExpr(Expr* fn, std::vector<Expr*> args) :
    fn(fn), args(args) {
}

CallExpr::CallExpr(Expr* fn): fn(fn) {
}

CallExpr::~CallExpr() {
  delete fn;
  for (auto a : args)
    delete a;
  args.clear();
}

Expr* CallExpr::getFunc() const {
  return fn;
}

std::vector<Expr*>& CallExpr::getArgs() {
  return args;
}

// For Printer
void CallExpr::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
