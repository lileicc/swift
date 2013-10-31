/*
* BooLiteral.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "BoolLiteral.h"

namespace swift{

BoolLiteral::BoolLiteral(int l, int c, bool value)
	:Literal(l, c, AbsynLiteralConstant::BOOL), value(value) {
}

BoolLiteral::~BoolLiteral() {
}

bool BoolLiteral::getValue() {
	return value;
}

// For Debugging Use
void BoolLiteral::print(FILE* file, int indent) {
	fprintf(file, "%*s(BoolLiteral: %s )\n", indent, "",
								(value ? "true" : "false"));
}

}