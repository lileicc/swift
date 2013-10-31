/*
* BoolLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef BOOLLITERAL_H_
#define BOOLLITERAL_H_

#include "Literal.h"

namespace swift {

class BoolLiteral :
	public swift::Literal
{
	bool value;
public:
	BoolLiteral(int l, int c, bool value);
	virtual ~BoolLiteral();

	bool getValue();

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif