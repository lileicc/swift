/*
 * BinaryOperator.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */
#include <vector>
#include "BinaryOperator.h"

namespace swift {
namespace code {

BinaryOperator::BinaryOperator(Expr* lhs, Expr* rhs, OpKind op) :
    Expr(std::vector<Expr*>( { lhs, rhs })), op(op) {
}

BinaryOperator::~BinaryOperator() {
}

Expr* BinaryOperator::getLeft() const {
  return args[0];
}

Expr* BinaryOperator::getRight() const {
  return args[1];
}

const OpKind& BinaryOperator::getOp() const {
  return op;
}

void BinaryOperator::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
