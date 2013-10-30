/*
* FuncApp.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef FUNCAPP_H_
#define FUNCAPP_H_

#include "Expr.h"
#include "Symbol.h"

namespace swift{

class FuncApp :
	public swift::Expr
{
	Symbol func;
public:
	FuncApp(int l, int c, Symbol func);
	virtual ~FuncApp();

	Symbol& getFunc();
};

}
#endif