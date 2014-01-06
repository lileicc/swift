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
  if(lhs != NULL) delete lhs;
  if(rhs != NULL) delete rhs;
}

Expr* ArraySubscriptExpr::getLeft() {
  return lhs;
}

Expr* ArraySubscriptExpr::getRight() {
  return rhs;
}

// For Printer
void ArraySubscriptExpr::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
