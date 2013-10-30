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

const Symbol& FuncDecl::getFunc() {
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

const VarDecl& FuncDecl::getArg(int k) {
	return args[k];
}

void FuncDecl::addArg(VarDecl var) {
	args.push_back(var);
}

}