/*
* VarDecl.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "VarDecl.h"

namespace swift{

VarDecl::VarDecl(int l, int c, Symbol typ, Symbol var)
	:Expr(l, c), typ(typ), var(var) {
}


VarDecl::~VarDecl() {
}

const Symbol& VarDecl::getTyp() {
	return typ;
}

const Symbol& VarDecl::getVar() {
	return var;
}

}