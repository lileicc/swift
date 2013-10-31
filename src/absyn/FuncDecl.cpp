/*
* FuncDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "FuncDecl.h"

namespace swift {

FuncDecl::FuncDecl(int l, int c, bool random, Symbol func, Expr* expr)
	:Decl(l, c, AbsynDeclConstant::FUNCTION), 
	 random(random), func(func), expr(expr) {
}

FuncDecl::~FuncDecl() {
	if (expr != NULL) delete expr;
}

Symbol& FuncDecl::getFunc() {
	return func;
}

bool FuncDecl::isRandom() {
	return random;
}

Expr* FuncDecl::getExpr() {
	return expr;
}

int FuncDecl::argSize() {
	return args.size();
}

VarDecl& FuncDecl::getArg(int k) {
	return args[k];
}

void FuncDecl::addArg(VarDecl var) {
	args.push_back(var);
}

// For Debugging Use
void FuncDecl::print(FILE* file, int indent) {
	fprintf(file, "%*s(FuncDecl:\n", indent, "");
	fprintf(file, "%*s:type %s\n", indent + 2, "", 
															(random ? "random" : "fixed"));
	fprintf(file, "%*s:func %s\n", indent + 2, "", func.getValue().c_str());
	fprintf(file, "%*s(args:\n", indent + 2, "");
	for (int i = 0; i < args.size(); i++)
		args[i].print(file, indent + 4);
	fprintf(file, "%*s)\n", indent + 2, "");
	fprintf(file, "%*s)\n", indent, "");
}

}