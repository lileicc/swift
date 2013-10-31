/*
* QueryDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "QueryDecl.h"

namespace swift {

QueryDecl::QueryDecl(int l, int c, Expr* expr)
	:Decl(l, c), expr(expr) {
}

QueryDecl::~QueryDecl() {
	if (expr != NULL) delete expr;
}

Expr* QueryDecl::getExpr() {
	return expr;
}

// For Debugging Use
void QueryDecl::print(FILE* file, int indent) {
	fprintf(file, "%*s(QueryDecl:\n", indent, "");
	if (expr != NULL)
	{
		fprintf(file, "%*s:expr\n", indent + 2, "");
		expr->print(file, indent + 4);
	}
	fprintf(file, "%*s)\n", indent, "");
}

}