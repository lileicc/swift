/*
 * CallClassConstructor.h
 *
 *  Created on: Jan 22, 2014
 *      Author: leili
 */

#pragma once

#include "Expr.h"
#include "Type.h"
#include "../printer/Printer.h"

namespace swift {
namespace code {

class CallClassConstructor: public swift::code::Expr {
public:
  CallClassConstructor(Type type, std::vector<Expr*> args =
      std::vector<Expr *>());
  virtual ~CallClassConstructor();
  Type& getType();
  void print(printer::Printer* prt);
protected:
  Type type;
};

} /* namespace code */
} /* namespace swift */
