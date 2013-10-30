/*
* TypDecl.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef TYPDECL_H_
#define TYPDECL_H_

#include<vector>
using std::vector;

#include "Decl.h"
#include "Symbol.h"

namespace swift {

class TypDecl :
	public swift::Decl
{
	vector<Symbol> args;
public:
	TypDecl(int l, int c);
	virtual ~TypDecl();

	int size();
	void add(Symbol typ);
	const Symbol& get(int k);
};

}

#endif