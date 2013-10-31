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
	Symbol arg;
public:
	TypDecl(int l, int c, Symbol arg);
	virtual ~TypDecl();

	Symbol& get();

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif