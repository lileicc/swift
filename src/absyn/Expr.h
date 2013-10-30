/*
 * Expr.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#ifndef EXPR_H_
#define EXPR_H_

#include<vector>
#include "Absyn.h"

namespace swift {

class Expr: public swift::Absyn {
public:
  Expr(int l, int c) : Absyn(l, c) {}
  virtual ~Expr();
  std::vector<Expr> args;
};

} /* namespace swift */

#endif /* EXPR_H_ */
