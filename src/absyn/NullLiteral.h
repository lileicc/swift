/*
* NullLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef NULLLITERAL_H_
#define NULLLITERAL_H_

#include "Literal.h"

namespace swift {

class NullLiteral :
	public swift::Literal
{
public:
	NullLiteral(int l, int c);
	virtual ~NullLiteral();
};

}

#endif