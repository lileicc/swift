/*
 * ArrayExpr.h
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace absyn {

class ArrayExpr: public Expr {
  int dim;
public:
  ArrayExpr(int l, int c, int dim = 1);
  virtual ~ArrayExpr();

  int getDim();

  // For Debugging Use
  void print(FILE* file, int indent);
  std::string toString();

  Expr* clone();
};

}
}
