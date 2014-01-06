/*
 * SpecialStmt.h
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#pragma once

/*
Special Statement can be any single statement in the source code.

Note that: ';' (if applicable) must be included!

For example:
   std::exit(0);
   using namespace std;
   #include <iostream>
   #define LL long long
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
  void print(printer::Printer* prt);

private:
  std::string stmt;
};

} /* namespace code */
} /* namespace swift */
