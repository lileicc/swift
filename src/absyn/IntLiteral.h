/*
* IntLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef INTLITERAL_H_
#define INTLITERAL_H_

#include "Literal.h"

namespace swift {

class IntLiteral :
	public swift::Literal
{
	int value;
public:
	IntLiteral(int l, int c, int value);
	virtual ~IntLiteral();

	int getValue();

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif