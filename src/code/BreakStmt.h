/*
 * BreakStmt.h
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"

namespace swift {
namespace code {

class BreakStmt: public swift::code::Stmt {
public:
  BreakStmt();
  ~BreakStmt();

  // For Printer
  void print(printer::CPPPrinter* prt);
};

} /* namespace code */
} /* namespace swift */
