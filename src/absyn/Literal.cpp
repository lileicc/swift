/*
* Literal.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "Literal.h"

namespace swift {

Literal::Literal(int l, int c, AbsynLiteralConstant typ)
	:Expr(l,c), typ(typ) {
}

Literal::~Literal()
{
}

}