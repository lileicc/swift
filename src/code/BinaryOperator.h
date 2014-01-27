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
  UO_CMPT,      // complement
  UO_NEG,       // negate
  UO_INC,       // increment
  UO_DEC,       // decrement
  UO_NEW,       // new or malloc
  UO_DEL,       // delete or dispose
  UO_ARRAY_DEL, // delete[] array
  // Binary Operator
  BO_ASSIGN,    // Assignment
  BO_FIELD,     // reference to a field
  BO_POINTER,   // pointer to a field
  BO_RANGE,     // Range Operator : i.e. for(auto p: args) in C++
  BO_LSHGT,     // binary left shift
  BO_RSHGT,     // binary right shift
  BO_BAND,      // binary and
  BO_BOR,       // binary or
  BO_XOR,       // binary xor
  BO_EQU,       // equal
  BO_NEQ,       // not equal
  BO_LT,        // less than
  BO_GT,        // greater than
  BO_LEQ,       // less then or equal
  BO_GEQ,       // greater then or equal
  BO_PLUS,      // plus
  BO_MINUS,     // minus
  BO_MUL,       // multiply
  BO_DIV,       // divide
  BO_MOD,       // module
  BO_POW,       // power
  BO_SPLUS,     // self plus
  BO_SMINUS,    // self minus
  BO_SMUL,      // self multiply
  BO_SDIV,      // self divide
  BO_SMOD,      // self module
  BO_SCOPE,     // scope operator, e.g. std::vector
  BO_COMMA      // comma operator, i.e. ","
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
  OpKind op;
};

} /* namespace code */
} /* namespace swift */
