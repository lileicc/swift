/*
 * Ty.h
 *
 *  Created on: Oct 31, 2013
 *      Author: yiwu
 */

#pragma once

#include <string>

#include "Symbol.h"

namespace swift {
namespace absyn {
class Ty {
  Symbol typ;
  int dim;
public:
  Ty(Symbol typ, int dim = 0);
  virtual ~Ty();

  Symbol& getTyp();
  int getDim();

  // For Debugging Use
  std::string toString();
};

}
}
