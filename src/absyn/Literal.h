/*
* Literal.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef LITERAL_H_
#define LITERAL_H_

#include "Expr.h"

namespace swift {

class Literal :
	public swift::Expr
{
public:
	Literal(int l, int c);
	virtual ~Literal();
};

}

#endif