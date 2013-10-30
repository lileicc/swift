/*
* QueryDecl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef QUERYDECL_H_
#define QUERYDECL_H_

#include "Decl.h"
#include "Expr.h"

namespace swift {

class QueryDecl :
	public swift::Decl
{
	Expr* expr;
public:
	QueryDecl(int l, int c, Expr* expr);
	virtual ~QueryDecl();

	Expr* getExpr();
};

}

#endif