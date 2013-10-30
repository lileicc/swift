/*
* DistrExpr.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "DistrExpr.h"

namespace swift{

DistrExpr::DistrExpr(int l,int r,Symbol distr)
	:Expr(l,r), distr(distr) {
}


DistrExpr::~DistrExpr() {
}

const Symbol& DistrExpr::getDistr(){
	return distr;
}

}