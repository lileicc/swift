/*
 * BoolLiteral.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include "Literal.h"

namespace swift {
namespace absyn {

class BoolLiteral: public Literal {
  bool value;
public:
  BoolLiteral(int l, int c, bool value);
  virtual ~BoolLiteral();

  bool getValue();

  // For Debugging Use
  void print(FILE* file, int indent);

  Expr* clone();
};

}
}
