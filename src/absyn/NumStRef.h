/*
* NumStRef.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef NUMSTREF_H_
#define NUMSTREF_H_

#include "Expr.h"

namespace swift {

class NumStRef :
	public swift::Expr
{
public:
	NumStRef(int l, int c, Expr* e);
	virtual ~NumStRef();

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif
