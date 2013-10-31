/*
* TypDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "TypDecl.h"

namespace swift {

TypDecl::TypDecl(int l, int c, Symbol arg)
	:Decl(l, c, AbsynDeclConstant::TYPE), arg(arg) {
}

TypDecl::~TypDecl() {
}

Symbol& TypDecl::get() {
	return arg;
}

// For Debugging Use
void TypDecl::print(FILE* file, int indent) {
	fprintf(file, "%*s(TypDecl: %s )\n", indent, "", arg.getValue().c_str());
}

}