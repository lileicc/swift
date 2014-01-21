/*
 * Type.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Type.h"

namespace swift {
namespace code {

Type::Type(const std::string name, bool refTag) : scope(nullptr), name(name), refTag(refTag) {
}

Type::Type(Expr* scope, std::string name, bool refTag) : scope(scope), name(name), refTag(refTag) {
}

Type::~Type() {
}

const std::string& Type::getName() const {
  return name;
}

bool Type::isRef() const {
  return refTag;
}

Expr* Type::getScope() {
  return scope;
}

// For Printer
void Type::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */


