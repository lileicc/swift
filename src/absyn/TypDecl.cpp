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

const Symbol& TypDecl::get(int k) {
	return args[k];
}

}