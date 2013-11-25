/*
 * CaseStmt.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "CaseStmt.h"

namespace swift {
namespace code {

CaseStmt::CaseStmt(Expr* val, Stmt* sub) : val(val), sub(sub) {
}

CaseStmt::~CaseStmt() {
  delete val;
  delete sub;
}

} /* namespace code */
} /* namespace swift */
