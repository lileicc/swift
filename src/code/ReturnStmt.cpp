/*
 * ReturnStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "ReturnStmt.h"

namespace swift {
namespace code {

ReturnStmt::ReturnStmt(Expr* expr) : expr(expr) {
}

ReturnStmt::~ReturnStmt() {
  if(expr != NULL) delete expr;
}

Expr* ReturnStmt::getExpr() const {
  return expr;
}

// For Printer
void ReturnStmt::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
