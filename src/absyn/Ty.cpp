/*
 * Ty.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: yiwu
 */

#include "Ty.h"

namespace swift {
namespace absyn {

Ty::Ty(Symbol typ, int dim)
  :line(0), col(0), typ(typ), dim(dim) {
}

Ty::Ty(int l, int c, Symbol typ, int dim)
: line(l), col(c), typ(typ), dim(dim) {
}

Ty::~Ty() {
}

const Symbol& Ty::getTyp() const {
  return typ;
}

int Ty::getDim() const {
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
