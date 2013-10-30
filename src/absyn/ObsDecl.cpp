/*
* ObsDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "ObsDecl.h"

namespace swift {

ObsDecl::ObsDecl(int l, int c, Expr* left, Expr* right)
	:Decl(l, c, AbsynDeclConstant::OBS), left(left), right(right) {
}

ObsDecl::~ObsDecl() {
	if (left != NULL) delete left;
	if (right != NULL) delete right;
}

Expr* ObsDecl::getLeft() {
	return left;
}

Expr* ObsDecl::getRight() {
	return right;
}

}