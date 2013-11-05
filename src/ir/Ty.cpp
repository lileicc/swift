/*
 * Ty.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#include "Ty.h"

#include "IRConst.h"

namespace swift {
namespace ir {
Ty::Ty(IRConstant typ)
  :typ(typ) {
}

Ty::~Ty() {
}

IRConstant Ty::getTyp() {
  return typ;
}

std::string Ty::toString() {
  // Type: for class Ty
  switch (typ) {
  case IRConstant::BOOL: return std::string("Bool");
  case IRConstant::INT: return std::string("Int");
  case IRConstant::DOUBLE: return std::string("Double");
  case IRConstant::STRING: return std::string("std::string");
  default: return std::string("NA");
  }
}

}
}
