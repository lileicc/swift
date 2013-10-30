/*
* Decl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef DECL_H_
#define DECL_H_

#include "Absyn.h"

namespace swift {

class Decl :
	public swift::Absyn
{
	AbsynDeclConstant typ;
public:
	Decl(int l, int c, AbsynDeclConstant typ);
	virtual ~Decl();
};

}

#endif