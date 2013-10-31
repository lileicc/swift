/*
* ListSet.h
*
*  Created on: Oct 31, 2013
*      Author: yiwu
*/

#pragma once

#include "SetExpr.h"

namespace swift {

class ListSet :
  public swift::SetExpr
{
public:
  ListSet(int l, int c);
  virtual ~ListSet();

  // For Debugging Use
  void print(FILE *file, int indent);
};

}