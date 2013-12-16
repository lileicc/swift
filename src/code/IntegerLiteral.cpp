/*
 * IntegerLiteral.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "IntegerLiteral.h"

namespace swift {
namespace code {

IntegerLiteral::IntegerLiteral(int v) : val(v) {
}

IntegerLiteral::~IntegerLiteral() {}

int IntegerLiteral::getVal() const {
  return val;
}

// For Printer
void IntegerLiteral::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
