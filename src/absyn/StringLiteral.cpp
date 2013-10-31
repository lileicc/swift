/*
* StringLiteral.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "StringLiteral.h"

namespace swift{

StringLiteral::StringLiteral(int l, int c, string value)
	:Literal(l, c, AbsynLiteralConstant::STRING), value(value) {
}

StringLiteral::~StringLiteral() {
}

const string& StringLiteral::getValue() {
	return value;
}

// For Debugging Use
void StringLiteral::print(FILE* file, int indent) {
	fprintf(file, "%*s(StringLiteral: %s )\n", indent, "", value.c_str());
}

}