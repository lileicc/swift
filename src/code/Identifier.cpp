/*
 * Identifier.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Identifier.h"

namespace swift {
namespace code {

Identifier::Identifier(std::string id) :
    id(id) {
}

Identifier::~Identifier() {
}

const std::string& Identifier::getId() const {
  return id;
}

// For Printer
void Identifier::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
