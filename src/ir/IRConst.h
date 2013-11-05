#pragma once

namespace swift {
namespace ir {

enum class IRConstant {
  // Not Available
  NA,
  // Type: for class Ty
  BOOL, INT, DOUBLE, STRING,
  NAMETY, ARRAY, MAP, SET,
  // Function Category: for FunctionDefn
  FIXED, RANDOM, ORIGIN,
  // Constant Symbol Category: for ConstSymbol
  INSTANCE, INTLITERAL, DOUBLELITERAL, BOOLLITERAL, STRINGLITERAL, NULLSYMBOL,
  // Operator: For OprExpr
  PLUS, MINUS, MUL, DIV, POWER, MOD,
  EQ, NEQ, LT, GT, LE, GE,
  AND, OR, NOT, IMPLY,
  SUB,
  // Quantified Formula: For QuantForm
  FORALL, EXISTS,
  // Set Type: for SetExpr
  LISTSET, CONDSET
};

}
}
