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
  BO_ASSIGN,         // Assignment
  BO_EQUAL,
  BO_FIELD           // reference to a field
};

class BinaryOperator: public swift::code::Expr {
public:
  BinaryOperator(Expr* lhs, Expr* rhs, OpKind op);
  ~BinaryOperator();

  Expr* getLeft() const ;
  Expr* getRight() const ;

  // For Printer
  void print(printer::CPPPrinter* prt);

private:
  Expr* lhs; // left hand side
  Expr* rhs; // right hand side
  OpKind op;
};

} /* namespace code */
} /* namespace swift */
