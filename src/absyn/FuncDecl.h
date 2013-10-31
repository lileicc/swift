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
  bool random;
  Symbol typ;
	Symbol func;
	Expr* expr;
	vector<VarDecl> args;

public:
	FuncDecl(int l, int c, bool random, Symbol typ, Symbol func, Expr* expr);
	virtual ~FuncDecl();

	Symbol& getFunc();
	Symbol& getTyp();
	Expr* getExpr();
	bool isRandom();
	size_t argSize();
	void addArg(VarDecl var);
	VarDecl& getArg(int k);

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif
