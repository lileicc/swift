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

ForStmt::ForStmt(): range(false) {
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

Expr* ForStmt::getStep() {
  return step;
}

void ForStmt::setStep(Expr* st) {
  step = st;
}

bool ForStmt::isRange() const {
  return range;
}

void ForStmt::setRange(bool r) {
  range = r;
}

void ForStmt::addStmt(Stmt* st) {
  body.addStmt(st);
}

CompoundStmt& ForStmt::getBody() {
  return body;
}

// For Printer
void ForStmt::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
