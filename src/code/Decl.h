/*
 * Decl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "../printer/Printer.h"

namespace swift {
namespace code {

class Decl {
public:
  Decl();
  virtual ~Decl();

  // For Printer
  virtual void print(printer::Printer* prt) = 0;
};

} /* namespace code */
} /* namespace swift */
