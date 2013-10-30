/*
* TimeStamp.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "TimeStampLiteral.h"

namespace swift{

TimeStampLiteral::TimeStampLiteral(int l, int c, int value)
	:Literal(l, c, AbsynLiteralConstant::INT), value(value) {
}

TimeStampLiteral::~TimeStampLiteral() {
}

int TimeStampLiteral::getValue() {
	return value;
}

}