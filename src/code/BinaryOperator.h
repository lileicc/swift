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
  // Unitary Operator
  BO_COMP, // complement
  BO_NEG, // negate
  BO_INC, // increment
  BO_DEC, // decrement
  BO_NEW, // new or malloc
  BO_DEL, // delete or dispose
  // Binary Operator
  BO_ASSIGN,   // Assignment
  BO_FIELD,    // reference to a field
  BO_RANGE,    // Range Operator : i.e. for(auto p: args) in C++
  BO_LSHGT,    // binary left shift
  BO_RSHGT,    // binary right shift
  BO_BAND,     // binary and
  BO_BOR,      // binary or
  BO_XOR,      // binary xor
  BO_EQU,      // equal
  BO_NEQ,      // not equal
  BO_LT,        // less than
  BO_GT, // greater than
  BO_LEQ, // less then or equal
  BO_GEQ, // greater then or equal
  BO_PLUS, // plus
  BO_MINUS, // minus
  BO_MUL, // multiply
  BO_DIV, // divide
  BO_MOD, // module
  BO_POW, // power
  BO_SPLUS, // self plus
  BO_SMINUS, // self minus
  BO_SMUL, // self multiply
  BO_SDIV, // self divide
  BO_SMOD // self module
};

class BinaryOperator: public swift::code::Expr {
public:
  BinaryOperator(Expr* lhs, Expr* rhs, OpKind op);
  ~BinaryOperator();

  Expr* getLeft() const ;
  Expr* getRight() const ;
  const OpKind& getOp() const ;
  
  // For Printer
  void print(printer::Printer* prt);

private:
  Expr* lhs; // left hand side
  Expr* rhs; // right hand side
  OpKind op;
};

} /* namespace code */
} /* namespace swift */
