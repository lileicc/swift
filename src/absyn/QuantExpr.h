/*
* QuantExpr.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#pragma once

#include "Expr.h"
#include "Symbol.h"
#include "VarDecl.h"

namespace swift {

class QuantExpr :
  public swift::Expr
{
  AbsynConstant typ;
  VarDecl var;
public:
  QuantExpr(int l, int c, 
      AbsynConstant typ, VarDecl var, Expr* cond);
  virtual ~QuantExpr();

  AbsynConstant getTyp();
  VarDecl& getVar();
  Expr* getCond();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}