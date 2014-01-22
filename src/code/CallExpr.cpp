/*
 * CallExpr.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: leili
 */

#include "CallExpr.h"
#include "Identifier.h"
#include "BinaryOperator.h"

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

CallExpr* CallExpr::createMethodCall(std::string varname,
    std::string methodname, std::vector<Expr*> args) {
  return new CallExpr(
      new BinaryOperator(new Identifier(varname), new Identifier(methodname),
          OpKind::BO_FIELD), args);
}

} /* namespace code */
} /* namespace swift */

