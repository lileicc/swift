/*
 * ArraySubscriptExpr.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "ArraySubscriptExpr.h"

namespace swift {
namespace code {

ArraySubscriptExpr::ArraySubscriptExpr(Expr* lhs, Expr* rhs) :
    Expr(std::vector<Expr*>( { lhs, rhs })) {
}

ArraySubscriptExpr::~ArraySubscriptExpr() {
}

Expr* ArraySubscriptExpr::getLeft() {
  return args[0];
}

Expr* ArraySubscriptExpr::getRight() {
  return args[1];
}

// For Printer
void ArraySubscriptExpr::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
