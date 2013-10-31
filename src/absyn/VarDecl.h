/*
* VarDecl.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*
*  Note :
*    This is not a DECL but an EXPR
*
*/

#pragma once

#include "Expr.h"
#include "Symbol.h"

namespace swift{

class VarDecl
  :public swift::Expr
{
  Symbol typ, var;
public:
  VarDecl(int l, int c, Symbol typ = Symbol(), Symbol var = Symbol());
  virtual ~VarDecl();

  Symbol& getVar();
  Symbol& getTyp();

  //For Debugging Use
  void print(FILE *file, int indent);
};

}