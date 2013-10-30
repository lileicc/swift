/*
* OriginDecl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef ORIGINDECL_H_
#define ORIGINDECL_H_

#include "Decl.h"
#include "Symbol.h"

namespace swift {

class OriginDecl :
	public swift::Decl
{
	Symbol func;
	Symbol arg;
public:
	OriginDecl(int l, int c, Symbol func, Symbol arg);
	virtual ~OriginDecl();

	const Symbol& getFunc();
	const Symbol& getArg();
};

}

#endif