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

Symbol& NumStDecl::getTyp() {
	return typ;
}

Expr* NumStDecl::getExpr() {
	return expr;
}

int NumStDecl::argSize() {
	return origin.size();
}

Symbol& NumStDecl::getArgOrigin(int k) {
	return origin[k];
}

Symbol& NumStDecl::getArgVar(int k) {
	return var[k];
}

void NumStDecl::add(Symbol o, Symbol v) {
	origin.push_back(o);
	var.push_back(v);
}

// For Debugging Use
void NumStDecl::print(FILE* file, int indent) {
	fprintf(file, "%*s(NumStDecl:\n", indent, "");
	fprintf(file, "%*s:type %s\n", indent + 2, "", typ.getValue().c_str());
	if (origin.size() > 0) {
		fprintf(file, "%*s(args:\n", indent + 2, "");
		for (int i = 0; i < origin.size(); i++)
		{
			fprintf(file, "%*sorigin#%d: %s", indent + 4, "", origin[i].getValue().c_str());
			fprintf(file, "%*svar#%d: %s", indent + 4, "", var[i].getValue().c_str());
		}
		fprintf(file, "%*s)\n", indent + 2, "");
	}
	if (expr != NULL) {
		fprintf(file, "%*s:expr\n", indent + 2, "");
		expr->print(file, indent + 4);
	}
	fprintf(file, "%*s)\n", indent, "");
}

}