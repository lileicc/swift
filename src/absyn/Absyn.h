/*
 * Absyn.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#ifndef ABSYN_H_
#define ABSYN_H_

#include <cstdio>

namespace swift {

enum class AbsynOpExprConstant {
	PLUS, MINUS, MUL, DIV, POWER, MOD,
	EQ, NEQ, LT, GT, LE, GE,
	AND, OR, NOT, IMPLY,
	SUB
};

enum class AbsynQuantExprConstant {
	FORALL, EXISTS
};

class Absyn {
public:
  Absyn(int l, int c) : line(l), col(c) {}
  virtual ~Absyn();
  int line; // line number in original file
  int col; // column number in original file

	// For Debugging Use
	virtual void print(FILE* file, int indent = 0) = 0;
};

} /* namespace swift */

#endif /* ABSYN_H_ */
