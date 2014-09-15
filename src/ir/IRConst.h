#pragma once

#include <string>

namespace swift {
namespace ir {

enum class IRConstant {
  // Not Available
  NA,
  // Type: for class Ty
  BOOL,
  INT,
  DOUBLE,
  STRING,
  TIMESTEP,
  NAMETY,
  ARRAY,
  MAP,
  SET,
  MATRIX,
  // Function Category: for FunctionDefn
  FIXED,
  RANDOM,
  ORIGIN,
  // Constant Symbol Category: for ConstSymbol
  INSTANCE,
  INTLITERAL,
  DOUBLELITERAL,
  BOOLLITERAL,
  STRINGLITERAL,
  NULLSYMBOL,
  // Operator: For OprExpr
  PLUS,
  MINUS,
  MUL,
  DIV,
  POWER,
  MOD,
  EQ,
  NEQ,
  LT,
  GT,
  LE,
  GE,
  AND,
  OR,
  NOT,
  IMPLY,
  SUB,
  PARENTHESES,
  // Quantified Formula: For QuantForm
  FORALL,
  EXISTS,
  // Set Type: for SetExpr
  LISTSET,
  CONDSET
};

class IRConstString {
public:
  static const std::string BOOL;
  static const std::string INT;
  static const std::string DOUBLE;
  static const std::string STRING;
  static const std::string TIMESTEP;
  static const std::string MATRIX;
  static const std::string NA;

  static const std::string BLOG_BOOL;
  static const std::string BLOG_INT;
  static const std::string BLOG_DOUBLE;
  static const std::string BLOG_STRING;
  static const std::string BLOG_TIMESTEP;
  static const std::string BLOG_MATRIX;
};

}
}
