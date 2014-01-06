/*
 * CaseStmt.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "CaseStmt.h"

namespace swift {
namespace code {

CaseStmt::CaseStmt(Expr* val) : val(val) {
}

CaseStmt::CaseStmt(Expr* val, Stmt* stmt) : val(val) {
  sub.addStmt(stmt);
}

CaseStmt::~CaseStmt() {
  delete val;
}

Expr* CaseStmt::getVal() {
  return val;
}

void CaseStmt::addStmt(Stmt* st) {
  sub.addStmt(st);
}

CompoundStmt& CaseStmt::getSub() {
  return sub;
}

// For Printer
void CaseStmt::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
