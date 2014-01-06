/*
 * BreakStmt.h
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#pragma once

/*
Special Statement can be any single statement in the source code.
For example:
   break;
   continue;
   std::exit(0);
etc.
 -- Yi Wu
*/

#include "Stmt.h"

#include <string>

namespace swift {
namespace code {

class SpecialStmt: public swift::code::Stmt {
public:
  SpecialStmt(std::string stmt = std::string("break"));
  ~SpecialStmt();

  const std::string& getStmt() const;

  // For Printer
  void print(printer::CPPPrinter* prt);

private:
  std::string stmt;
};

} /* namespace code */
} /* namespace swift */
