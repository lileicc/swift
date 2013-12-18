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
  if (cond != NULL) delete cond;
  for (auto p: body)
    if (p != NULL) delete p;
}

Expr* SwitchStmt::getCond() const {
  return cond;
}

void SwitchStmt::addCase(CaseStmt* st) {
  body.push_back(st);
}

size_t SwitchStmt::size() const {
  return body.size();
}

CaseStmt* SwitchStmt::get(int k) const {
  return body[k];
}

const std::vector<CaseStmt*>& SwitchStmt::getAll() const {
  return body;
}

// For Printer
void SwitchStmt::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
