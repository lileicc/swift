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

#ifndef OPEXPR_H_
#define OPEXPR_H_

#include "Expr.h"

namespace swift {

class OpExpr: public swift::Expr {
	AbsynOpExprConstant op;
public:
  OpExpr(int l, int c, AbsynOpExprConstant op, Expr* left, Expr* right);
  virtual ~OpExpr();

	AbsynOpExprConstant getOp();
	Expr* getLeft();
	Expr* getRight();
};

} /* namespace swift */

#endif /* OPEXPR_H_ */
