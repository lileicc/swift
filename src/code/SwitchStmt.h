/*
 * SwitchStmt.h
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#pragma once

#include <vector>
#include "Stmt.h"
#include "Expr.h"
#include "CaseStmt.h"

namespace swift {
namespace code {

class SwitchStmt: public swift::code::Stmt {
public:
  SwitchStmt(Expr* cond);
  ~SwitchStmt();

  Expr* getCond() const;
  void addCase(CaseStmt* st);
  CaseStmt* get(int k) const;
  size_t size() const;
  const std::vector<CaseStmt*>& getAll() const;

  // For Printer
  void print(printer::CPPPrinter* prt);

private:
  Expr* cond;
  std::vector<CaseStmt*> body;
};

} /* namespace code */
} /* namespace swift */
