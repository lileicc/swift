/*
 * SwitchStmt.h
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"
#include "Expr.h"
#include "CompoundStmt.h"

namespace swift {
namespace code {

/**
 * A switch statement accepts an expression, based whose value it will jump to
 * the corresponding case statement
 */
class SwitchStmt: public swift::code::Stmt {
public:
  SwitchStmt(Expr* cond);
  ~SwitchStmt();

  Expr* getCond() const;
  void addStmt(Stmt* st);
  
  CompoundStmt* getBody();
  // For Printer
  void print(printer::Printer* prt);

private:
  Expr* cond;
  CompoundStmt body;
};

} /* namespace code */
} /* namespace swift */
