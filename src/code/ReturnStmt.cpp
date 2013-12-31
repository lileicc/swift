/*
 * ReturnStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "ReturnStmt.h"

namespace swift {
namespace code {

ReturnStmt::ReturnStmt(Expr* expr) : expr(expr) {
}

ReturnStmt::~ReturnStmt() {
  delete expr;
}

} /* namespace code */
} /* namespace swift */
