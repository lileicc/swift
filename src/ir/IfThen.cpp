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

IfThen::IfThen(std::shared_ptr<Expr> cond, std::shared_ptr<Clause> thcl, std::shared_ptr<Clause> elcl)
  :cond(cond), thcl(thcl), elcl(elcl) {
}

IfThen::~IfThen() {
}

void IfThen::setCond(std::shared_ptr<Expr> e) {
  cond = e;
}

void IfThen::setThen(std::shared_ptr<Clause> c) {
  thcl = c;
}

void IfThen::setElse(std::shared_ptr<Clause> c) {
  elcl = c;
}

std::shared_ptr<Expr> IfThen::getCond() {
  return cond;
}

std::shared_ptr<Clause> IfThen::getThen() {
  return thcl;
}

std::shared_ptr<Clause> IfThen::getElse() {
  return elcl;
}

}
}

