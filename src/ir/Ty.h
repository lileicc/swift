/*
 * Type.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once

#include "IRHeader.h"

namespace swift {
namespace ir {
class Ty {
  IRConstant typ;
public:
  Ty(IRConstant typ = IRConstant::NA);
  virtual ~Ty();

  IRConstant getTyp();
};
}
}
