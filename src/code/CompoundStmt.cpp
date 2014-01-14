/*
 * CompoundStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CompoundStmt.h"

namespace swift {
namespace code {

CompoundStmt::CompoundStmt() {
  // TODO Auto-generated constructor stub

}

CompoundStmt::~CompoundStmt() {
  // TODO Auto-generated destructor stub
  for (auto p: body)
    if (p != NULL) delete p;
}

void CompoundStmt::addStmt(Stmt* st) {
  body.push_back(st);
}

size_t CompoundStmt::size() const {
  return body.size();
}

Stmt* CompoundStmt::get(int k) const {
  return body[k];
}

const std::vector<Stmt*>& CompoundStmt::getAll() const {
  return body;
}

// For Printer
void CompoundStmt::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
