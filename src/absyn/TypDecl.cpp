/*
* TypDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "TypDecl.h"

namespace swift {

TypDecl::TypDecl(int l, int c)
	:Decl(l, c, AbsynDeclConstant::TYPE) {
}

TypDecl::~TypDecl() {
}

int TypDecl::size() {
	return args.size();
}

void TypDecl::add(Symbol sym) {
	args.push_back(sym);
}

Symbol& TypDecl::get(int k) {
	return args[k];
}

// For Debugging Use
void TypDecl::print(FILE* file, int indent) {
	fprintf(file, "%*s(TypDecl:\n", indent, "");
	fprintf(file, "%*s(:", indent + 2, "");
	for (int i = 0; i < args.size(); i++)
		fprintf(file, " %s", args[i].getValue().c_str());
	fprintf(file, " )\n");
	fprintf(file, "%*s)\n", indent, "");
}

}