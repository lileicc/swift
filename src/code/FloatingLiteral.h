/*
 * FloatingLiteral.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace code {

class FloatingLiteral: public swift::code::Expr {
public:
  FloatingLiteral(double val);
  ~FloatingLiteral();

  double getVal() const;

  // For Printer
  void print(printer::Printer* prt);

private:
  double val;
};

} /* namespace code */
} /* namespace swift */
