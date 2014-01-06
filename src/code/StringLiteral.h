/*
 * IntegerLiteral.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

#include <string>

namespace swift {
namespace code {

class StringLiteral: public swift::code::Expr {
public:
  StringLiteral(std::string v);
  ~StringLiteral();

  const std::string& getVal() const ;
  // For Printer
  void print(printer::Printer* prt);
private:
  std::string val;
};

} /* namespace code */
} /* namespace swift */
