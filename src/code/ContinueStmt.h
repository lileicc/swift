/*
 * ContinueStmt.h
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"

namespace swift {
namespace code {

class ContinueStmt: public swift::code::Stmt {
public:
  ContinueStmt();
  ~ContinueStmt();

  // For Printer
  void print(printer::Printer* prt);
};

} /* namespace code */
} /* namespace swift */
