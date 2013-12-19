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

class IntegerLiteral: public swift::code::Expr {
public:
  IntegerLiteral(int v);
  ~IntegerLiteral();

  int getVal() const ;
  // For Printer
  void print(printer::Printer* prt);
private:
  int val;
};

} /* namespace code */
} /* namespace swift */
