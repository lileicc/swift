/*
* ObsDecl.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "ObsDecl.h"

namespace swift {

ObsDecl::ObsDecl(int l, int c, Expr* left, Expr* right)
	:Decl(l, c), left(left), right(right) {
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

// For Debugging Use
void ObsDecl::print(FILE* file, int indent) {
	fprintf(file, "%*s(ObsDecl:\n", indent, "");
	if (left != NULL)
	{
		fprintf(file, "%*s:left\n", indent + 2, "");
		left->print(file, indent + 4);
	}
	if (right != NULL)
	{
		fprintf(file, "%*s:right\n", indent + 2, "");
		left->print(file, indent + 4);
	}
	fprintf(file, "%*s)\n", indent, "");
}

}