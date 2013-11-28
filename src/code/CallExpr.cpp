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
}

} /* namespace code */
} /* namespace swift */
