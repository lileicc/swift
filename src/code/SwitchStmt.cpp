/*
 * SwitchStmt.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#include "SwitchStmt.h"

namespace swift {
namespace code {

SwitchStmt::SwitchStmt(Expr * cond) : cond(cond) {
}

SwitchStmt::~SwitchStmt() {
}

void SwitchStmt::addStmt(Stmt* st) {
  body.addStmt(st);
}

} /* namespace code */
} /* namespace swift */
