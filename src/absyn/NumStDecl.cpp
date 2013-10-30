/*
* NumStDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "NumStDecl.h"

namespace swift {

NumStDecl::NumStDecl(int l, int c, Symbol typ, Expr* expr)
	:Decl(l, c, AbsynDeclConstant::NUMBERSTMT), typ(typ), expr(expr) {
}

NumStDecl::~NumStDecl() {
	if (expr != NULL) delete expr;
}

const Symbol& NumStDecl::getTyp() {
	return typ;
}

Expr* NumStDecl::getExpr() {
	return expr;
}

int NumStDecl::argSize() {
	return origin.size();
}

const Symbol& NumStDecl::getArgOrigin(int k) {
	return origin[k];
}

const Symbol& NumStDecl::getArgVar(int k) {
	return var[k];
}

void NumStDecl::add(Symbol o, Symbol v) {
	origin.push_back(o);
	var.push_back(v);
}

}