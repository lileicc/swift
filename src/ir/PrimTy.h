/*
 * PrimTy.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include "Type.h"
namespace swift {
namespace ir {
class PrimTy: public Type {
public:
  PrimTy();
  ~PrimTy();
  std::string name;
};
}
}
