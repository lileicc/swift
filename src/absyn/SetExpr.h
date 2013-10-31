/*
* SetExpr.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#pragma once

#include "Expr.h"
#include "Symbol.h"

namespace swift {

class SetExpr :
  public swift::Expr
{
public:
  SetExpr(int l, int c);
  virtual ~SetExpr();
};

}