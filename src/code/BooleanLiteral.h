/*
 * IntegerLiteral.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace code {

class BooleanLiteral: public swift::code::Expr {
public:
  BooleanLiteral(bool v);
  ~BooleanLiteral();

  bool getVal() const;
  // For Printer
  void print(printer::Printer* prt);
private:
  bool val;
};

} /* namespace code */
} /* namespace swift */
