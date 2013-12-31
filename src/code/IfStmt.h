/*
 * IfStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include "Stmt.h"
#include "Expr.h"

namespace swift {
namespace code {

class IfStmt: public swift::code::Stmt {
public:
  IfStmt(Expr* cond, Stmt* th, Stmt* el);
  ~IfStmt();
private:
  Expr* cond;
  Stmt* th;
  Stmt* el;
};

} /* namespace code */
} /* namespace swift */