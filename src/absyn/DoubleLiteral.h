/*
* DoubleLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef DOUBLELITERAL_H_
#define DOUBLELITERAL_H_

#include "Literal.h"

namespace swift {

class DoubleLiteral :
	public swift::Literal
{
	double value;
public:
	DoubleLiteral(int l, int c, double value);
	virtual ~DoubleLiteral();

	double getValue();

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif
