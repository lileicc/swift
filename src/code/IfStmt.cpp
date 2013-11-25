/*
 * IfStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "IfStmt.h"

namespace swift {
namespace code {

IfStmt::IfStmt(Expr* cond, Stmt* th, Stmt* el) : cond(cond), th(th), el(el) {
}

IfStmt::~IfStmt() {
  delete cond;
  delete th;
  delete el;
}

} /* namespace code */
} /* namespace swift */
