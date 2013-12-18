/*
 * Type.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Type.h"

namespace swift {
namespace code {

Type::Type(std::string name, bool refTag) : name(name), refTag(refTag) {
}

Type::~Type() {
}

const std::string& Type::getName() {
  return name;
}

bool Type::isRef() {
  return refTag;
}

// For Printer
void Type::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
