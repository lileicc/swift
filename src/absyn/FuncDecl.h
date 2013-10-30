/*
* FuncDecl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef FUNCDECL_H_
#define FUNCDECL_H_

#include <vector>
using std::vector;

#include "Decl.h"
#include "Expr.h"
#include "Symbol.h"
#include "VarDecl.h"

namespace swift {

class FuncDecl :
	public swift::Decl
{
	Symbol func;
	vector<VarDecl> args;
	Expr* expr;
	bool random;
public:
	FuncDecl(int l, int c, bool random, Symbol func, Expr* expr);
	virtual ~FuncDecl();

	const Symbol& getFunc();
	Expr* getExpr();
	bool isRandom();
	int argSize();
	void addArg(VarDecl var);
	const VarDecl& getArg(int k);
};

}

#endif