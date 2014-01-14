/*
 * Type.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once

#include <string>

#include "IRConst.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {
class Ty {
public:
  Ty(IRConstant typ = IRConstant::NA);
  virtual ~Ty();

  IRConstant getTyp() const;

  virtual std::string toString() const;

private:
  IRConstant typ;
};
}
}
