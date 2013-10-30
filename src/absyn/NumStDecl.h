/*
* NumStDecl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef NUMSTDECL_H_
#define NUMSTDECL_H_

#include <vector>
using std::vector;

#include "Decl.h"
#include "Expr.h"
#include "Symbol.h"

namespace swift {

class NumStDecl :
	public swift::Decl
{
	Symbol typ;
	vector<Symbol> origin;
	vector<Symbol> var;
	Expr* expr;
public:
	NumStDecl(int l, int c, Symbol typ, Expr* expr);
	virtual ~NumStDecl();

	Expr* getExpr();
	Symbol& getTyp();
	int argSize();
	Symbol& getArgOrigin(int k);
	Symbol& getArgVar(int k);
	void add(Symbol o, Symbol v);
};

}

#endif
