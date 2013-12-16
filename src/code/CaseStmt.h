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

class CaseStmt: public swift::code::Stmt {
public:
  CaseStmt(Expr* val);
  CaseStmt(Expr* val, Stmt* sub);
  ~CaseStmt();

  void addStmt(Stmt* st);
  CompoundStmt& getSub();
  Expr* getVal();

  // For Printer
  void print(printer::CPPPrinter* prt);
private:
  Expr* val;
  CompoundStmt sub;
};

} /* namespace code */
} /* namespace swift */
