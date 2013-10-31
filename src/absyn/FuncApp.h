/*
* FuncApp.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#pragma once

#include "Expr.h"
#include "Symbol.h"

namespace swift{

class FuncApp :
  public swift::Expr
{
  Symbol func;
public:
  FuncApp(int l, int c, Symbol func);
  virtual ~FuncApp();

  Symbol& getFuncName();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}