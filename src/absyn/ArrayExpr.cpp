/*
* ArrayExpr.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "ArrayExpr.h"

namespace swift {

ArrayExpr::ArrayExpr(int l, int c, int dim)
	:Expr(l, c), dim(dim) {
}

ArrayExpr::~ArrayExpr() {
}

}