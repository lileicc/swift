/*
 * IntegerLiteral.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "StringLiteral.h"

namespace swift {
namespace code {

StringLiteral::StringLiteral(std::string v) :
    val(v) {
}

StringLiteral::~StringLiteral() {
}

const std::string& StringLiteral::getVal() const {
  return val;
}

// For Printer
void StringLiteral::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
