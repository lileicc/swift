/*
 * BreakStmt.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "BreakStmt.h"

namespace swift {
namespace code {

BreakStmt::BreakStmt() {
}

BreakStmt::~BreakStmt() {
}

void BreakStmt::print(printer::Printer* prt) {
  prt->print(this);
}
} /* namespace code */
} /* namespace swift */
