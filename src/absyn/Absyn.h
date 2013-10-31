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

enum AbsynOpExprConstant {
	PLUS, MINUS, MUL, DIV, POWER, MOD,
	EQ, NEQ, LT, GT, LE, GE,
	AND, OR, NOT, IMPLY,
	SUB
};

enum AbsynLiteralConstant {
	INT, DOUBLE, BOOL, STRING,
	TIMESTAMP,
	NULLEXPR
};

enum AbsynDeclConstant {
	TYPE, DISTINCT, NUMBERSTMT, ORIGIN, 
	FUNCTION, QUERY, OBS
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
