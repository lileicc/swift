/*
* QuantExpr.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef QUANTExprDECL_H_
#define QUANTDECL_H_

#include "Expr.h"
#include "Symbol.h"
#include "VarDecl.h"

namespace swift {

class QuantExpr :
	public swift::Expr
{
	AbsynQuantExprConstant typ;
	VarDecl var;
public:
	QuantExpr(int l, int c, 
			AbsynQuantExprConstant typ, VarDecl var, Expr* cond);
	virtual ~QuantExpr();

	AbsynQuantExprConstant getTyp();
	VarDecl& getVar();
	Expr* getCond();

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif