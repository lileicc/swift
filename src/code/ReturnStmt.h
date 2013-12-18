/*
 * ReturnStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"
#include "Expr.h"

namespace swift {
namespace code {

class ReturnStmt: public swift::code::Stmt {
public:
  ReturnStmt(Expr* expr);
  ~ReturnStmt();

  Expr* getExpr();

  // For Printer
  void print(printer::CPPPrinter* prt);
private:
  Expr* expr;
};

} /* namespace code */
} /* namespace swift */
