/*
 * ForStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "ForStmt.h"

#include "CompoundStmt.h"

namespace swift {
namespace code {

ForStmt::ForStmt() {
  // TODO Auto-generated constructor stub
  init = NULL;
  cond = NULL;
  step = NULL;
}

ForStmt::~ForStmt() {
  // TODO Auto-generated destructor stub
  if (init != NULL) delete init;
  if (cond != NULL) delete cond;
  if (step != NULL) delete step;
}

Stmt* ForStmt::getInit() {
  return init;
}

void ForStmt::setInit(Stmt* it) {
  init = it;
}

Expr* ForStmt::getCond() {
  return cond;
}

void ForStmt::setCond(Expr* cd) {
  cond = cd;
}

Stmt* ForStmt::getStep() {
  return step;
}

void ForStmt::setStep(Stmt* st) {
  step = st;
}

void ForStmt::addStmt(Stmt* st) {
  body.addStmt(st);
}

CompoundStmt& ForStmt::getBody() {
  return body;
}

// For Printer
void ForStmt::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
