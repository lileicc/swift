/*
 * CaseStmt.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "CaseStmt.h"

namespace swift {
namespace code {

CaseStmt::CaseStmt(Expr* val, Stmt* stmt) :
    val(val), sub(stmt) {
}

CaseStmt::~CaseStmt() {
  delete val;
  if (sub != NULL)
    delete sub;
}

Expr* CaseStmt::getVal() const {
  return val;
}

Stmt* CaseStmt::getSub() const {
  return sub;
}

// For Printer
void CaseStmt::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
