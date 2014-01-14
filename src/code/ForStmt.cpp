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

ForStmt::ForStmt(Stmt* init, Expr* cond, Expr* step, Stmt* body) :
    init(init), cond(cond), step(step), body(body), range(false) {
}

ForStmt::~ForStmt() {
  delete init;
  delete cond;
  delete step;
  delete body;
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

Stmt* ForStmt::getBody() {
  return body;
}

// For Printer
void ForStmt::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
