/*
* Evidence.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#pragma once

#include "Expr.h"
#include "Stmt.h"

namespace swift {
  namespace absyn {

class Evidence :
  public Stmt
{
  Expr* left;
  Expr* right;
public:
  Evidence(int l, int c, Expr* left, Expr* right);
  virtual ~Evidence();
  
  Expr* getLeft();
  Expr* getRight();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}}