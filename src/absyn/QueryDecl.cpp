/*
* QueryDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "QueryDecl.h"

namespace swift {

QueryDecl::QueryDecl(int l, int c, Expr* expr)
	:Decl(l, c, AbsynDeclConstant::QUERY), expr(expr) {
}

QueryDecl::~QueryDecl() {
	if (expr != NULL) delete expr;
}

Expr* QueryDecl::getExpr() {
	return expr;
}

}