/*
* ObsDecl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef OBSDECL_H_
#define OBSDECL_H_

#include "Decl.h"
#include "Expr.h"

namespace swift {

class ObsDecl :
	public swift::Decl
{
	Expr* left;
	Expr* right;
public:
	ObsDecl(int l, int c, Expr* left, Expr* right);
	virtual ~ObsDecl();
	
	Expr* getLeft();
	Expr* getRight();
};

}
#endif