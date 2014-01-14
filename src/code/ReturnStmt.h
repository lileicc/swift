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
  ReturnStmt(Expr* expr = NULL);
  ~ReturnStmt();

  Expr* getExpr() const;

  // For Printer
  void print(printer::Printer* prt);
private:
  Expr* expr;
};

} /* namespace code */
} /* namespace swift */
