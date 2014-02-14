/*
 * Semant.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#include "Clause.h"

#include "Ty.h"
#include "ArrayTy.h"
#include "SetTy.h"

namespace swift {
namespace ir {
Clause::Clause(const Ty* typ) :
    typ(typ) {
  _is_random = false;
}

Clause::~Clause() {
}

void Clause::setTyp(const Ty* ty) {
  typ = ty;
}

const Ty* Clause::getTyp() const {
  return typ;
}

void Clause::setRandom(bool r) {
  _is_random = r;
}

bool Clause::isRandom() {
  return _is_random;
}

}
}
