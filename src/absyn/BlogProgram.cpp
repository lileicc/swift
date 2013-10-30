/*
* BlogProgram.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "BlogProgram.h"

namespace swift {

BlogProgram::BlogProgram(int l, int c)
	:Absyn(l, c) {
}

BlogProgram::~BlogProgram() {
	for (int i = 0; i < args.size(); i++)
		if (args[i] != NULL)
			delete args[i];
}

int BlogProgram::size() {
	return args.size();
}

void BlogProgram::add(Decl* decl) {
	args.push_back(decl);
}

Decl* BlogProgram::get(int k) {
	return args[k];
}

}