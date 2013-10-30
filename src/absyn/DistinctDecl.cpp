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

const Symbol& DistinctDecl::getTyp() {
	return typ;
}

const Symbol& DistinctDecl::getVar(int k) {
	return var[k];
}

int DistinctDecl::getRep(int k) {
	return rep[k];
}

}