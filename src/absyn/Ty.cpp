/*
 * Ty.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: yiwu
 */

#include "Ty.h"

namespace swift {
namespace absyn {

Ty::Ty(Symbol typ, int dim) :
    typ(typ), dim(dim) {
}

Ty::~Ty() {
}

const Symbol& Ty::getTyp() const {
  return typ;
}

int Ty::getDim() {
  return dim;
}

std::string Ty::toString() {
  std::string ret(typ.getValue());
  for (int i = 0; i < dim; i++)
    ret.append("[]");
  return ret;
}

}
}
