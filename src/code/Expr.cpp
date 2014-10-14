/*
 * Expr.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Expr.h"

namespace swift {
namespace code {

Expr::Expr(std::vector<Expr*> args) :
    args(args) {
}

Expr::~Expr() {
  for (auto& a : args)
    if(a != NULL) delete a;
  args.clear();
}

std::vector<code::Expr*>& Expr::getArgs() {
  return args;
}

void Expr::clearArgs() {
  args.clear();
}

} /* namespace code */
} /* namespace swift */
