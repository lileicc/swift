/*
* VarDecl.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*
*  Note :
*    This is not a DECL but an EXPR
*
*/

#ifndef VARDECL_H_
#define VARDECL_H_

#include "Expr.h"
#include "Symbol.h"

namespace swift{

class VarDecl :
	public swift::Expr
{
	Symbol typ, var;
public:
	VarDecl(int l, int c, Symbol typ, Symbol var);
	virtual ~VarDecl();

	const Symbol& getVar();
	const Symbol& getTyp();
};

}

#endif