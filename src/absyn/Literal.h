/*
* Literal.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#pragma once

#include "Expr.h"

namespace swift {

class Literal :
  public swift::Expr
{
public:
  Literal(int l, int c);
  virtual ~Literal();
};

}