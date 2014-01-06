/*
 * ContinueStmt.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "ContinueStmt.h"

namespace swift {
namespace code {

ContinueStmt::ContinueStmt() {
}

ContinueStmt::~ContinueStmt() {
}

void ContinueStmt::print(printer::Printer* prt) {
  prt->print(this);
}
} /* namespace code */
} /* namespace swift */
