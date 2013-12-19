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
  void addStmt(Stmt* st);
  void setBody(CompoundStmt b);
  CompoundStmt& getBody();
  
  // For Printer
  void print(printer::Printer* prt);

private:
  Expr* cond;
  CompoundStmt body;
};

} /* namespace code */
} /* namespace swift */
