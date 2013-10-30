/*
* DistinctDecl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#ifndef DISTINCTDECL_H_
#define DISTINCTDECL_H_

#include <vector>
using std::vector;

#include "Decl.h"
#include "Symbol.h"

namespace swift {

class DistinctDecl :
	public swift::Decl
{
	Symbol typ;
	vector<Symbol> var;
	vector<int> rep;
public:
	DistinctDecl(int l, int c, Symbol typ);
	virtual ~DistinctDecl();

	int size();
	Symbol& getTyp();
	Symbol& getVar(int k);
	int getRep(int k);
	void add(Symbol v, int r = 1);
};

}

#endif