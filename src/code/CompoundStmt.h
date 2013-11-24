/*
 * CompoundStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"

namespace swift {
namespace code {

class CompoundStmt: public swift::code::Stmt {
public:
  CompoundStmt();
  ~CompoundStmt();
};

} /* namespace code */
} /* namespace swift */
