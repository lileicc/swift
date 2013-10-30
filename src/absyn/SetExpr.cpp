/*
* SetExpr.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "SetExpr.h"

namespace swift {

SetExpr::SetExpr(int l, int c, Symbol* typ, Symbol* var, Expr* cond)
	:Expr(l,c), typ(typ), var(var), cond(cond) {
}

SetExpr::~SetExpr() {
	if (typ != NULL) delete typ;
	if (var != NULL) delete var;
	if (cond != NULL) delete cond;
}

Symbol* SetExpr::getTyp() {
	return typ;
}

Symbol* SetExpr::getVar() {
	return var;
}

Expr* SetExpr::getCond() {
	return cond;
}

}