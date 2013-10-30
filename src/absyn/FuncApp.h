/*
* FuncApp.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef FUNCAPP_H_
#define FUNCAPP_H_

#include "Expr.h"

class FuncApp :
	public swift::Expr
{
public:
	FuncApp();
	virtual ~FuncApp();
};

#endif