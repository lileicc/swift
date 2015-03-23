/*
 * DoubleLiteral.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "DoubleLiteral.h"

namespace swift {
namespace absyn {

DoubleLiteral::DoubleLiteral(int l, int c, double value) :
    Literal(l, c), value(value) {
}

DoubleLiteral::~DoubleLiteral() {
}

double DoubleLiteral::getValue() {
  return value;
}

// For Debugging Use
void DoubleLiteral::print(FILE* file, int indent) {
  fprintf(file, "%*s(DoubleLiteral: %f )\n", indent, "", value);
}

std::string DoubleLiteral::toString() {
  return std::to_string(value);
}

Expr* DoubleLiteral::clone() {
  return new DoubleLiteral(line, col, value);
}

}
}
