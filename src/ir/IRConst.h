#pragma once

namespace swift {
namespace ir {

enum class IRConstant {
  // Not Available
  NA,
  // Type: for class Ty
  BOOL, INT, DOUBLE, STRING,
  NAMETY, ARRAY, MAP,
  // Function Category: for FunctionDefn
  FIXED, RANDOM, ORIGIN,
  // Constant Symbol Category: for ConstSymbol
  INSTANCE, INTLITERAL, DOUBLELITERAL, BOOLLITERAL, STRINGLITERAL, NULLSYMBOL
};

}
}
