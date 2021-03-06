/*
 * IntLiteral.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "IntLiteral.h"

namespace swift {
namespace absyn {

IntLiteral::IntLiteral(int l, int c, int value) :
    Literal(l, c), value(value) {
}

IntLiteral::~IntLiteral() {
}

int IntLiteral::getValue() {
  return value;
}

// For Debugging Use
void IntLiteral::print(FILE* file, int indent) {
  fprintf(file, "%*s(IntLiteral: %d )\n", indent, "", value);
}

std::string IntLiteral::toString() {
  return std::to_string(value);
}

Expr* IntLiteral::clone() {
  return new IntLiteral(line, col, value);
}

}
}
