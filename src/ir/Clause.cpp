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
Clause::Clause(Ty* typ)
  :typ(typ) {
}

Clause::~Clause() {
}

void Clause::setTyp(Ty* ty) {
  typ = ty;
}

Ty* Clause::getTyp()  {
  return typ;
}

}
}
