/*
 * IfStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "IfStmt.h"

namespace swift {
namespace code {

IfStmt::IfStmt(Expr* cond) : cond(cond) {
}

IfStmt::IfStmt(Expr* cond, Stmt* th_st, Stmt* el_st) : cond(cond) {
  th.addStmt(th_st);
  el.addStmt(el_st);
}

IfStmt::~IfStmt() {
  delete cond;
}

Expr* IfStmt::getCond() {
  return cond;
}

CompoundStmt& IfStmt::getThen() {
  return th;
}

CompoundStmt& IfStmt::getElse() {
  return el;
}

// For Printer
void IfStmt::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
