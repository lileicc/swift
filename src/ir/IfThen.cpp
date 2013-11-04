/*
 * IfThen.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#include "IfThen.h"

#include "Expr.h"

namespace swift {
namespace ir {

IfThen::IfThen(Expr* cond, Clause* thcl, Clause* elcl)
  :cond(cond), thcl(thcl), elcl(elcl) {
}

IfThen::~IfThen() {
  if (cond != NULL) delete cond;
  if (thcl != NULL) delete thcl;
  if (elcl != NULL) delete elcl;
}

void IfThen::setCond(Expr* e) {
  cond = e;
}

void IfThen::setThen(Clause *c) {
  thcl = c;
}

void IfThen::setElse(Clause *c) {
  elcl = c;
}

Expr* IfThen::getCond() {
  return cond;
}

Clause* IfThen::getThen() {
  return thcl;
}

Clause* IfThen::getElse() {
  return elcl;
}

}
}

