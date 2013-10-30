/*
* SetExpr.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*
*  Note :
*    3 ways of defining a set
*     { typ }
*     { typ var : cond }
*     { ele1, ele2, ... }
    in each way, some fields might be empty
*/

#ifndef SETEXPR_H_
#define SETEXPR_H_

#include "Expr.h"
#include "Symbol.h"

namespace swift {

class SetExpr :
	public swift::Expr
{
	Symbol* typ;
	Symbol* var;
	Expr* cond;
public:
	SetExpr(int l, int c, Symbol* typ = NULL, Symbol* var = NULL, Expr* cond = NULL);
	virtual ~SetExpr();

	Symbol* getTyp();
	Symbol* getVar();
	Expr* getCond();
};

}

#endif