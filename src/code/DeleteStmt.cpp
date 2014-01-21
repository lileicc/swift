/*
 * DeleteStmt.cpp
 *
 *  Created on: Jan 13, 2014
 *      Author: leili
 */

#include "DeleteStmt.h"

namespace swift {
namespace code {
DeleteStmt::~DeleteStmt() {
  delete var;
}

DeleteStmt::DeleteStmt(Identifier* var, bool arrayDel) :
    var(var), arrayDel(arrayDel) {
}

bool DeleteStmt::isArray() const {
  return arrayDel;
}

Identifier* DeleteStmt::getVar() {
  return var;
}

void DeleteStmt::print(printer::Printer* prt) {
  prt->print(this);
}
} /* namespace code */
} /* namespace swift */
