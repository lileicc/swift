/*
* NumStRef.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "NumStRef.h"

namespace swift {

NumStRef::NumStRef(int l, int c, Expr* e)
	:Expr(l, c) {
	args.push_back(e);
}

NumStRef::~NumStRef() {
}

}