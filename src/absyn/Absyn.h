/*
 * Absyn.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#pragma once

#include <cstdio>

namespace swift {
namespace absyn {

enum class AbsynConstant {
  // For OpExpr
  PLUS_,
  MINUS_,
  MUL_,
  DIV_,
  POWER_,
  MOD_,
  EQ_,
  NEQ_,
  LT_,
  GT_,
  LE_,
  GE_,
  AND_,
  OR_,
  NOT_,
  IMPLY_,
  SUB_,
  AT_,
  // For QuantExpr
  FORALL_,
  EXISTS_
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

}
}
