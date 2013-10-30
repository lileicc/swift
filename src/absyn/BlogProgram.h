/*
* BlogProgram.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*
*  Note :
*    This node appears only ONCE in the syntax tree
*
*/

#ifndef BLOGPROGRAM_H_
#define BLOGPROGRAM_H_

#include <vector>
using std::vector;

#include "Absyn.h"
#include "Decl.h"

namespace swift {

class BlogProgram :
	public swift::Absyn
{
	vector<Decl*> args;
public:
	BlogProgram(int l, int r);
	virtual ~BlogProgram();

	int size();
	void add(Decl* decl);
	Decl* get(int k);
};

}

#endif