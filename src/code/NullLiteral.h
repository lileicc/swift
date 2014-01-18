/*
 * NullLiteral.h
 *
 *  Created on: Jan 17, 2014
 *      Author: leili
 */

#pragma once

#include "Expr.h"
#include "../printer/Printer.h"

namespace swift {
namespace code {

class NullLiteral: public swift::code::Expr {
public:
  NullLiteral();
  ~NullLiteral();
  void print(printer::Printer* prt);
};

} /* namespace code */
} /* namespace swift */
