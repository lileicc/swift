/*
* VarRef.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "VarRef.h"

namespace swift{

VarRef::VarRef(int l, int c, Symbol var)
	:Expr(l,c), var(var) {
}


VarRef::~VarRef() {
}

Symbol& VarRef::getVar() {
	return var;
}

}