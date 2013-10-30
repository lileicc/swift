/*
* OriginDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "OriginDecl.h"

namespace swift {

OriginDecl::OriginDecl(int l, int c, Symbol func, Symbol arg)
	:Decl(l, c, AbsynDeclConstant::ORIGIN), func(func), arg(arg) {
}

OriginDecl::~OriginDecl() {
}

Symbol& OriginDecl::getArg() {
	return arg;
}

Symbol& OriginDecl::getFunc() {
	return func;
}

}