/*
 * VarRef.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "VarRef.h"

namespace swift {
namespace code {

VarRef::VarRef(std::string id) : id(id) {
}

VarRef::~VarRef() {
}

const std::string& VarRef::getId() const {
  return id;
}

// For Printer
void VarRef::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
