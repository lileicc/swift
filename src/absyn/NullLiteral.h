/*
 * NullLiteral.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include "Literal.h"

namespace swift {
namespace absyn {

class NullLiteral: public Literal {
public:
  NullLiteral(int l, int c);
  virtual ~NullLiteral();

  // For Debugging Use
  void print(FILE* file, int indent);
  Expr* clone();
};

}
}
