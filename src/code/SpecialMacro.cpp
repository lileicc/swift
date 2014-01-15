/*
 * SpecialMacro.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "SpecialMacro.h"

namespace swift {
namespace code {

SpecialMacro::SpecialMacro(std::string stmt): stmt(stmt) {
}

SpecialMacro::~SpecialMacro() {
}

const std::string& SpecialMacro::getMacro() const {
  return stmt;
}

void SpecialMacro::print(printer::Printer* prt) {
  prt->print(this);
}
} /* namespace code */
} /* namespace swift */
