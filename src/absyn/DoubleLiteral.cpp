/*
* DoubleLiteral.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "DoubleLiteral.h"

namespace swift{

DoubleLiteral::DoubleLiteral(int l, int c, double value)
	:Literal(l, c, AbsynLiteralConstant::DOUBLE), value(value) {
}

DoubleLiteral::~DoubleLiteral() {
}

double DoubleLiteral::getValue() {
	return value;
}

// For Debugging Use
void DoubleLiteral::print(FILE* file, int indent) {
	fprintf(file, "%*s(DoubleLiteral: %f )\n", indent, "", value);
}

}