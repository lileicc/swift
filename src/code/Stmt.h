/*
 * Stmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "../printer/CPPPrinter.h"

namespace swift {
namespace code {

class Stmt {
public:
  Stmt();
  ~Stmt();

  // For Printer
  virtual void print(printer::CPPPrinter* prt) = 0;
};

} /* namespace code */
} /* namespace swift */
