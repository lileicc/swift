/*
 * DeclStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"

namespace swift {
namespace code {

class DeclStmt: public swift::code::Stmt {
public:
  DeclStmt();
  ~DeclStmt();
};

} /* namespace code */
} /* namespace swift */
