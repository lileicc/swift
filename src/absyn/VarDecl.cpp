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

Symbol& VarDecl::getTyp() {
	return typ;
}

Symbol& VarDecl::getVar() {
	return var;
}

}