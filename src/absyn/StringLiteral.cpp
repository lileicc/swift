/*
 * StringLiteral.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "StringLiteral.h"

namespace swift {
namespace absyn {

StringLiteral::StringLiteral(int l, int c, std::string value) :
    Literal(l, c), value(value) {
}

StringLiteral::~StringLiteral() {
}

const std::string& StringLiteral::getValue() {
  return value;
}

// For Debugging Use
void StringLiteral::print(FILE* file, int indent) {
  fprintf(file, "%*s(StringLiteral: %s )\n", indent, "", value.c_str());
}

std::string StringLiteral::toString() {
  return "\"" + value + "\"";
}

Expr* StringLiteral::clone() {
  return new StringLiteral(line, col, value);
}

}
}
