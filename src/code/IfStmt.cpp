/*
 * IfStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "IfStmt.h"

namespace swift {
namespace code {

IfStmt::IfStmt(Expr* cond, Stmt* th, Stmt* el) :
    cond(cond), th(th), el(el) {
}

IfStmt::~IfStmt() {
  delete cond;
}

Expr* IfStmt::getCond() {
  return cond;
}

Stmt* IfStmt::getThen() {
  return th;
}

Stmt* IfStmt::getElse() {
  return el;
}

// For Printer
void IfStmt::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
