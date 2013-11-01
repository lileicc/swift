/*
* TimeStampLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#pragma once

#include "Literal.h"

namespace swift {

class TimeStampLiteral :
  public swift::Literal
{
  int value;
public:
  TimeStampLiteral(int l, int c, int value);
  virtual ~TimeStampLiteral();

  int getValue();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}