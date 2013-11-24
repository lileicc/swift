/*
 * ForStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"

namespace swift {
namespace code {

class ForStmt: public swift::code::Stmt {
public:
  ForStmt();
  ~ForStmt();
};

} /* namespace code */
} /* namespace swift */
