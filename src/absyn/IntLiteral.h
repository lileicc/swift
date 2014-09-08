/*
 * IntLiteral.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include "Literal.h"

namespace swift {
namespace absyn {

class IntLiteral: public Literal {
  int value;
public:
  IntLiteral(int l, int c, int value);
  virtual ~IntLiteral();

  int getValue();

  // For Debugging Use
  void print(FILE* file, int indent);
  Expr* clone();
};

}
}
