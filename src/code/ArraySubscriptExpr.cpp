/*
 * ArraySubscriptExpr.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "ArraySubscriptExpr.h"

namespace swift {
namespace code {

ArraySubscriptExpr::ArraySubscriptExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {
}

ArraySubscriptExpr::~ArraySubscriptExpr() {
  delete lhs;
  delete rhs;
}

} /* namespace code */
} /* namespace swift */
