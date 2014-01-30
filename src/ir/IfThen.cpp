/*
 * IfThen.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#include "IfThen.h"

#include "Expr.h"
#include <iostream>
using namespace std;

namespace swift {
namespace ir {

IfThen::IfThen(std::shared_ptr<Expr> cond, std::shared_ptr<Clause> thcl,
    std::shared_ptr<Clause> elcl) :
    cond(cond), thcl(thcl), elcl(elcl) {
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

std::shared_ptr<Expr> IfThen::getCond() const {
  return cond;
}

std::shared_ptr<Clause> IfThen::getThen() const {
  return thcl;
}

std::shared_ptr<Clause> IfThen::getElse() const {
  return elcl;
}

void IfThen::print(FILE* file, int indent) const {
  fprintf(file, "%*s(IfThen:\n", indent, "");
  if (getCond() != nullptr) {
    fprintf(file, "%*scond:\n", indent + 2, "");
    getCond()->print(file, indent + 4);
  }
  if (getThen() != nullptr) {
    fprintf(file, "%*sthen:\n", indent + 2, "");
    getThen()->print(file, indent + 4);
  }
  if (getElse() != nullptr) {
    fprintf(file, "%*selse:\n", indent + 2, "");
    getElse()->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}

