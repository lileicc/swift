/*
 * Semant.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once

#include "IRForwardDecl.h"

#include "Ty.h"

namespace swift {
namespace ir {

class Clause {
public:
  Clause();
  virtual ~Clause();
  void setType(Ty* ty);
private:
  Ty* ty;
};

}
}
