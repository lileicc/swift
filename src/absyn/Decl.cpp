/*
* Decl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "Decl.h"

namespace swift {

Decl::Decl(int l, int c, AbsynDeclConstant typ)
	:Absyn(l, c), typ(typ) {
}

Decl::~Decl() {
}

}