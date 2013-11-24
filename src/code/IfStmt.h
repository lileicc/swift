/*
 * IfStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include "Stmt.h"

namespace swift {
namespace code {

class IfStmt: public swift::code::Stmt {
public:
  IfStmt();
  ~IfStmt();
};

} /* namespace code */
} /* namespace swift */
