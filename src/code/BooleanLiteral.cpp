/*
 * IntegerLiteral.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "BooleanLiteral.h"

namespace swift {
namespace code {

BooleanLiteral::BooleanLiteral(bool v) : val(v) {
}

BooleanLiteral::~BooleanLiteral() {}

bool BooleanLiteral::getVal() const {
  return val;
}

// For Printer
void BooleanLiteral::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
