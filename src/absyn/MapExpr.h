/*
* MapExpr.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef MAPEXPR_H_
#define MAPEXPR_H_

#include "Expr.h"

namespace swift {

class MapExpr :
	public swift::Expr
{
public:
	MapExpr(int l, int c);
	virtual ~MapExpr();

	int mapSize();
	Expr* getFrom(int k);
	Expr* getTo(int k);
	void addMap(Expr* from, Expr* to);

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif