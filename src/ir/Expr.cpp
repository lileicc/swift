/*
 * Expr.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#include "Expr.h"
namespace swift {
namespace ir {
Expr::Expr() {
}

Expr::~Expr() {
}

void Expr::addArg(Expr * expr) {
  args.push_back(expr);
}
std::vector<Expr*> Expr::getArgs() {
  return args;
}
}
}
