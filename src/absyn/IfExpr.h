/*
 * IfExpr.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#ifndef IFEXPR_H_
#define IFEXPR_H_

#include "Expr.h"

namespace swift {

class IfExpr: public swift::Expr {
public:
  IfExpr(int l, int c, Expr cond, Expr then_clause, Expr else_clause) :
      Expr(l, c) {
    // TODO put these three expr into args
  }
  virtual ~IfExpr();
};

} /* namespace swift */

#endif /* IFEXPR_H_ */
