/*
 * OpExpr.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "OpExpr.h"

namespace swift {

OpExpr::OpExpr(int l, int c, AbsynOpExprConstant op, Expr* left, Expr* right)
	:Expr(l,c),op(op) {
		args.push_back(left);
		args.push_back(right);
}

OpExpr::~OpExpr() {
}

AbsynOpExprConstant OpExpr::getOp() {
	return op;
}

Expr* OpExpr::getLeft() {
	return args[0];
}

Expr* OpExpr::getRight() {
	return args[1];
}

} /* namespace swift */
