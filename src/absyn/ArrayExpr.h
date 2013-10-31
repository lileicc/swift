/*
* ArrayExpr.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef ARRAYEXPR_H_
#define ARRAYEXPR_H_

#include "Expr.h"

namespace swift {

class ArrayExpr :
	public swift::Expr
{
	int dim;
public:
	ArrayExpr(int l, int c, int dim = 1);
	virtual ~ArrayExpr();

	int getDim();

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif