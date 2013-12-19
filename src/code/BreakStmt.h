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

<<<<<<< Upstream, based on origin/semant
/**
 * Representing a statement which can be used in for, while, and switch statements
 */
class BreakStmt: public swift::code::Stmt {
public:
  BreakStmt();
  ~BreakStmt();

  // For Printer
  void print(printer::CPPPrinter* prt);
=======
class BreakStmt: public swift::code::Stmt {
public:
  BreakStmt();
  ~BreakStmt();

  // For Printer
  void print(printer::Printer* prt);
>>>>>>> cf66c4e update printer
};

} /* namespace code */
} /* namespace swift */
