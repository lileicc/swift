/*
 * Expr.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#include "Expr.h"

namespace swift {
  namespace absyn {

Expr::Expr(int l, int c)
  :Absyn(l, c) {
}

Expr::~Expr() {
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      delete args[i];
}

void Expr::add(Expr* e) {
  args.push_back(e);
}

Expr* Expr::get(int id) {
  return args[id];
}

size_t Expr::size() {
  return args.size();
}

}}