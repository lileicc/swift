/*
 * Absyn.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#pragma once

#include <cstdio>

namespace swift {

enum class AbsynConstant {
  // For OpExpr
  PLUS, MINUS, MUL, DIV, POWER, MOD,
  EQ, NEQ, LT, GT, LE, GE,
  AND, OR, NOT, IMPLY,
  SUB,
  // For QuantExpr
  FORALL, EXISTS
};

class Absyn {
public:
  Absyn(int l, int c);
  virtual ~Absyn();
  int line; // line number in original file
  int col; // column number in original file

  // For Debugging Use
  virtual void print(FILE* file, int indent = 0) = 0;
};

} /* namespace swift */
