/*
* VarRef.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#pragma once

#include "Expr.h"
#include "Symbol.h"

namespace swift{

class VarRef :
  public swift::Expr
{
  Symbol var;
public:
  VarRef(int l, int c, Symbol var);
  virtual ~VarRef();

  Symbol& getVar();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}