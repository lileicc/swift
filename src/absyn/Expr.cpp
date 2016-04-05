/*
 * Expr.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#include "Expr.h"

namespace swift {
namespace absyn {

Expr::Expr(int l, int c) :
    Absyn(l, c) {
}

Expr::~Expr() {
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      delete args[i];
}

void Expr::add(Expr* e) {
  args.push_back(e);
}

void Expr::add_front(Expr* e) {
  args.insert(args.begin(), e);
}

Expr* Expr::get(size_t id) {
  return args[id];
}

std::vector<Expr*>& Expr::getAllExpr() {
  return args;
}

size_t Expr::size() {
  return args.size();
}

void Expr::cloneArgs() {
  for (size_t i = 0; i < args.size(); ++ i)
    if (args[i] != NULL)
      args[i] = args[i]->clone();
}

void Expr::clearArgs() {
  args.clear();
}

}
}
