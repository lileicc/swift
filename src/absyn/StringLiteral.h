/*
* StringLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#pragma once

#include<string>

#include "Literal.h"

namespace swift {

class StringLiteral :
  public swift::Literal
{
  std::string value;
public:
  StringLiteral(int l, int c, std::string value);
  virtual ~StringLiteral();

  const std::string& getValue();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}