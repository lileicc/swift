/*
 * CaseStmt.h
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"
#include "Expr.h"

namespace swift {
namespace code {

class CaseStmt: public swift::code::Stmt {
public:
  CaseStmt(Expr* val, Stmt* sub);
  ~CaseStmt();
private:
  Expr* val;
  Stmt* sub;
};

} /* namespace code */
} /* namespace swift */
