/*
* Decl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#pragma once

#include "Absyn.h"
#include "Stmt.h"

namespace swift {

class Decl :
  public swift::Stmt
{
public:
  Decl(int l, int c);
  virtual ~Decl();
};

}