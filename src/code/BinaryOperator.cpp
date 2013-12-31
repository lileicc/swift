/*
 * BinaryOperator.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "BinaryOperator.h"

namespace swift {
namespace code {

BinaryOperator::BinaryOperator(Expr* lhs, Expr* rhs, OpKind op) : lhs(lhs), rhs(rhs), op(op) {
}

BinaryOperator::~BinaryOperator() {
  delete lhs;
  delete rhs;
}

} /* namespace code */
} /* namespace swift */
