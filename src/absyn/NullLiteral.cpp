/*
* NullLiteral.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "NullLiteral.h"

namespace swift {

NullLiteral::NullLiteral(int l, int c)
	:Literal(l, c, AbsynLiteralConstant::NULLEXPR) {
}

NullLiteral::~NullLiteral() {
}

}