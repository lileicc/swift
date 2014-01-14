/*
 * IfStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include "Stmt.h"
#include "Expr.h"

#include "CompoundStmt.h"

namespace swift {
namespace code {

class IfStmt: public swift::code::Stmt {
public:
  IfStmt(Expr* cond);
  IfStmt(Expr* cond, Stmt* th_st, Stmt* el_st);
  ~IfStmt();

  Expr* getCond();
  CompoundStmt& getThen();
  CompoundStmt& getElse();

  // For Printer
  void print(printer::Printer* prt);
private:
  Expr* cond;
  CompoundStmt th;
  CompoundStmt el;
};

} /* namespace code */
} /* namespace swift */
