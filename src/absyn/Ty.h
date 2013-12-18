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
public:
  int line; // line number in original file
  int col; // column number in original file

  Ty(Symbol typ, int dim = 0);
  Ty(int l, int c, Symbol typ, int dim = 0);
  virtual ~Ty();

  const Symbol& getTyp() const;
  int getDim() const;

  // For Debugging Use
  std::string toString() const;

private:
  Symbol typ;
  int dim;
};

}
}
