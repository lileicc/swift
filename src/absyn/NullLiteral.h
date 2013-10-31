/*
* NullLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#pragma once

#include "Literal.h"

namespace swift {

class NullLiteral :
  public swift::Literal
{
public:
  NullLiteral(int l, int c);
  virtual ~NullLiteral();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}