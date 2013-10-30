/*
* DistrExpr.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef DISTREXPR_H_
#define DISTREXPR_H_

#include "Expr.h"
#include "Symbol.h"

namespace swift{

class DistrExpr :
	public swift::Expr
{
	Symbol distr;
public:
	DistrExpr(int l, int c, Symbol distr);
	virtual ~DistrExpr();

	Symbol& getDistr();
};

}
#endif