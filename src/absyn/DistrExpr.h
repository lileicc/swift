/*
* DistrExpr.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#pragma once

#include "Expr.h"
#include "Symbol.h"

namespace swift{ namespace absyn {

class DistrExpr :
  public Expr
{
  Symbol distr;
public:
  DistrExpr(int l, int c, Symbol distr);
  virtual ~DistrExpr();

  Symbol& getDistrName();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}