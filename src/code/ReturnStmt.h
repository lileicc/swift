/*
 * ReturnStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"

namespace swift {
namespace code {

class ReturnStmt: public swift::code::Stmt {
public:
  ReturnStmt();
  ~ReturnStmt();
};

} /* namespace code */
} /* namespace swift */
