/*
 * BinaryOperator.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace code {

enum class OpKind {
  BO_ASSIGN         // Assignment
};

class BinaryOperator: public swift::code::Expr {
public:
  BinaryOperator(Expr* lhs, Expr* rhs, OpKind op);
  ~BinaryOperator();
private:
  Expr* lhs; // left hand side
  Expr* rhs; // right hand side
  OpKind op;
};

} /* namespace code */
} /* namespace swift */
