/*
 * Type.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#include "Ty.h"
namespace swift {
namespace ir {
Ty::Ty(IRConstant typ)
  :typ(typ) {
}

IRConstant Ty::getTyp() {
  return typ;
}

}
}
