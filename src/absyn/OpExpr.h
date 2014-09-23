/*
 * OpExpr.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 *
 *  Note:
 *    When Dealing with Unary Operator e.g. NOT
 *        Left Child should be set NULL
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace absyn {

class OpExpr: public Expr {
  AbsynConstant op;
public:
  OpExpr(int l, int c, AbsynConstant op, Expr* left, Expr* right);
  virtual ~OpExpr();

  AbsynConstant getOp();
  Expr* getLeft();
  Expr* getRight();

  // For Debugging Use
  void print(FILE* file, int indent);
  Expr* clone();
};

}
} /* namespace swift */
