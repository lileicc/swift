/*
 * OpExpr.h
 *
 *  Created on: Oct 29, 2013
 *      Author: leili
 */

#ifndef OPEXPR_H_
#define OPEXPR_H_

#include "Expr.h"

namespace swift {

class OpExpr: public swift::Expr {
public:
  OpExpr(int l, int c, int op, Expr left, Expr right);
  virtual ~OpExpr();
};

} /* namespace swift */

#endif /* OPEXPR_H_ */
