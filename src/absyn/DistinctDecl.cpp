/*
* DistinctDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "DistinctDecl.h"

namespace swift {

DistinctDecl::DistinctDecl(int l, int c, Symbol typ)
	:Decl(l, c, AbsynDeclConstant::DISTINCT), typ(typ) {
}

DistinctDecl::~DistinctDecl() {
}

void DistinctDecl::add(Symbol v, int r) {
	var.push_back(v);
	rep.push_back(r);
}

int DistinctDecl::size() {
	return var.size();
}

Symbol& DistinctDecl::getTyp() {
	return typ;
}

Symbol& DistinctDecl::getVar(int k) {
	return var[k];
}

int DistinctDecl::getRep(int k) {
	return rep[k];
}

// For Debugging Use
void DistinctDecl::print(FILE* file, int indent) {
	fprintf(file, "%*s(DistinctDecl:\n", indent, "");
	fprintf(file, "%*s:type %s\n", indent + 2 , "", typ.getValue().c_str());
	fprintf(file, "%*s:var (:", indent + 2, "");
	for (int i = 0; i < var.size(); i++)
		fprintf(file, " %s", var[i].getValue().c_str());
	fprintf(file, " )\n");
	fprintf(file, "%*s)\n", indent, "");
}

}