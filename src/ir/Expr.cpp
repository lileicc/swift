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

const std::vector<Expr*>& Expr::getArgs() {
  return args;
}

size_t Expr::argSize() {
  return args.size();
}

Expr* Expr::get(int k)  {
  return args[k];
}

}
}
