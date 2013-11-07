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

void Expr::addArg(std::shared_ptr<Expr> expr) {
  args.push_back(expr);
}

const std::vector<std::shared_ptr<Expr>>& Expr::getArgs() {
  return args;
}

size_t Expr::argSize() {
  return args.size();
}

std::shared_ptr<Expr> Expr::get(int k) {
  return args[k];
}

}
}
