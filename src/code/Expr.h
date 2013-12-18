/*
 * Expr.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"

namespace swift {
namespace code {

class Expr: public swift::code::Stmt {
public:
  Expr();
  virtual ~Expr();

  // For Printer
  virtual void print(printer::CPPPrinter* prt) = 0;
};

} /* namespace code */
} /* namespace swift */
