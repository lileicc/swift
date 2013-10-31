/*
 * OpExpr.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: leili
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

// For Debugging Use
void OpExpr::print(FILE* file, int indent) {
	fprintf(file, "%*s(OpExpr:\n", indent, "");
	fprintf(file, "%*s:op %d\n", indent + 2, "", op);
	if (args[0] != NULL)
	{
		fprintf(file, "%*s:left\n", indent + 2, "");
		args[0]->print(file, indent + 4);
	}
	if (args[1] != NULL)
	{
		fprintf(file, "%*s:right\n", indent + 2, "");
		args[1]->print(file, indent + 4);
	}
	fprintf(file, "%*s)\n", indent, "");
}

} /* namespace swift */
