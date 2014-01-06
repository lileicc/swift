/*
 * BreakStmt.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "SpecialStmt.h"

namespace swift {
namespace code {

SpecialStmt::SpecialStmt(std::string stmt): stmt(stmt) {
}

SpecialStmt::~SpecialStmt() {
}

const std::string& SpecialStmt::getStmt() const {
  return stmt;
}

void SpecialStmt::print(printer::CPPPrinter* prt) {
  prt->print(this);
}
} /* namespace code */
} /* namespace swift */
