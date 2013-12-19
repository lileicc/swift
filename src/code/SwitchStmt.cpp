/*
 * SwitchStmt.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "SwitchStmt.h"

namespace swift {
namespace code {

SwitchStmt::SwitchStmt(Expr * cond) : cond(cond) {
}

SwitchStmt::~SwitchStmt() {
  delete cond;
}

Expr* SwitchStmt::getCond() const {
  return cond;
}

void SwitchStmt::addStmt(Stmt* st) {
  body.addStmt(st);
}

void SwitchStmt::setBody(CompoundStmt b) {
  body = b;
}

CompoundStmt& SwitchStmt::getBody() {
  return body;
}

// For Printer
void SwitchStmt::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
