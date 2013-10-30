/*
* VarRef.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef VARREF_H_
#define VARREF_H_

#include "Expr.h"
#include "Symbol.h"

namespace swift{

class VarRef :
	public swift::Expr
{
	Symbol var;
public:
	VarRef(int l, int c, Symbol var);
	virtual ~VarRef();

	Symbol& getVar();
};

}

#endif