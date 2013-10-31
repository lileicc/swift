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

// For Debugging Use
void SetExpr::print(FILE* file, int indent) {
	fprintf(file, "%*s(SetExpr:\n", indent, "");
	if (typ != NULL)
		fprintf(file, "%*s:typ %s\n", indent + 2, "", typ->getValue().c_str());
	if (var != NULL)
		fprintf(file, "%*s:var %s\n", indent + 2, "", var->getValue().c_str());
	if (cond != NULL) {
		fprintf(file, "%*s:cond\n", indent + 2, "");
		cond->print(file, indent + 4);
	}
	fprintf(file, "%*s)\n", indent, "");
}

}