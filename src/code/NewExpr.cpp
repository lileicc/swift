/*
 * NewExpr.cpp
 *
 *  Created on: Jan 13, 2014
 *      Author: leili
 */

#include "NewExpr.h"

namespace swift {
namespace code {

NewExpr::NewExpr(Expr* expr): ty("NULL"),expr(expr),arrayTag(false) {
}

NewExpr::~NewExpr() {
  delete expr;
}

NewExpr::NewExpr(Type ty, Expr* size) : ty(ty), expr(size), arrayTag(true) {
}

void NewExpr::print(printer::Printer* prt) {
  prt->print(this);
}

Type& swift::code::NewExpr::getType()  {
  return ty;
}

Expr* swift::code::NewExpr::getExpr() const {
  return expr;
}

bool swift::code::NewExpr::isArray() const {
  return arrayTag;
}

} /* namespace code */
} /* namespace swift */


