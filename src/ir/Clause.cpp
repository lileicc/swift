/*
 * Semant.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#include "Clause.h"

#include "Ty.h"

namespace swift {
namespace ir {
Clause::Clause(const Ty* typ)
  :typ(typ) {
}

Clause::~Clause() {
}

void Clause::setTyp(const Ty* ty) {
  typ = ty;
}

const Ty* Clause::getTyp()  {
  return typ;
}

}
}
