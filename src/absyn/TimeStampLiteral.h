/*
* TimeStampLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef TIMESTAMPLITERAL_H_
#define TIMESTAMPLITERAL_H_

#include "Literal.h"

namespace swift {

class TimeStampLiteral :
	public swift::Literal
{
	int value;
public:
	TimeStampLiteral(int l, int c, int value);
	virtual ~TimeStampLiteral();

	int getValue();
};

}

#endif