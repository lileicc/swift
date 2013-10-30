/*
 * IfExpr.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#include "IfExpr.h"

namespace swift {

IfExpr::IfExpr(int l, int r, Expr* cond, Expr* then_clause, Expr* else_clause) :Expr(l, r) {
	args.push_back(cond);
	args.push_back(then_clause);
	args.push_back(else_clause);
}

IfExpr::~IfExpr() {
}

Expr* IfExpr::getCond() {
	return args[0];
}

Expr* IfExpr::getThen() {
	return args[1];
}

Expr* IfExpr::getElse() {
	return args[2];
}

} /* namespace swift */
