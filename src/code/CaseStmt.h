/*
 * CaseStmt.h
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
 * A statement that can only be used inside switch statement.
 */
class CaseStmt: public swift::code::Stmt {
public:
  CaseStmt(Expr* val, Stmt* stmt = NULL);
  ~CaseStmt();

  Stmt* getSub() const;
  Expr* getVal() const;

  // For Printer
  void print(printer::Printer* prt);
private:
  Expr* val;
  Stmt* sub;
};

} /* namespace code */
} /* namespace swift */
