/*
 * BooLiteral.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "BoolLiteral.h"

namespace swift {
namespace absyn {

BoolLiteral::BoolLiteral(int l, int c, bool value) :
    Literal(l, c), value(value) {
}

BoolLiteral::~BoolLiteral() {
}

bool BoolLiteral::getValue() {
  return value;
}

// For Debugging Use
void BoolLiteral::print(FILE* file, int indent) {
  fprintf(file, "%*s(BoolLiteral: %s )\n", indent, "",
      (value ? "true" : "false"));
}

Expr* BoolLiteral::clone() {
  return new BoolLiteral(line, col, value);
}

}
}
