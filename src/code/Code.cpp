/*
 * Code.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Code.h"
#include "../printer/CPPPrinter.h"

namespace swift {
namespace code {

Code::Code() {
}

Code::~Code() {
  for (auto mc : macros)
    delete mc;
}

void Code::print(printer::Printer* prt) {
  prt->print(this);
}

void swift::code::Code::addMacro(SpecialMacro* macro) {
  macros.push_back(macro);
}

std::vector<SpecialMacro*>& swift::code::Code::getAllMacros() {
  return macros;
}

} /* namespace code */
} /* namespace swift */

