/*
* Stmt.h
*
*  Created on: Oct 31, 2013
*      Author: yiwu
*/

#pragma once

#include "Absyn.h"

namespace swift {

class Stmt :
  public swift::Absyn
{
public:
  Stmt(int l, int c);
  virtual ~Stmt();
};

}