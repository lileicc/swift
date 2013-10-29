/*
 * Expr.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#ifndef EXPR_H_
#define EXPR_H_

#include "Absyn.h"

#include<vector>
using namespace std;

namespace swift {

class Expr: public swift::Absyn {
public:
  Expr(int l, int c) : Absyn(l, c) {}
  virtual ~Expr();
  vector<Expr> args;
};

} /* namespace swift */

#endif /* EXPR_H_ */
