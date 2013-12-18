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
  if(lhs != NULL) delete lhs;
  if(rhs != NULL) delete rhs;
}

Expr* BinaryOperator::getLeft() const {
  return lhs;
}

Expr* BinaryOperator::getRight() const {
  return rhs;
}

const OpKind& BinaryOperator::getOp() const {
  return op;
}

void BinaryOperator::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
