/*
 * NewExpr.cpp
 *
 *  Created on: Jan 13, 2014
 *      Author: leili
 */

#include "NewExpr.h"

namespace swift {
namespace code {

NewExpr::NewExpr(Expr* expr) {
  ty("NULL");
  this->expr = expr;
  isArray = false;
}

NewExpr::~NewExpr() {
  delete expr;
}

NewExpr::NewExpr(Type ty, Expr* size) : ty(ty), expr(size), isArray(true) {
}

void NewExpr::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
