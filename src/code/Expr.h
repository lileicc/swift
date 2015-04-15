/*
 * Expr.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <vector>
#include "Stmt.h"

namespace swift {
namespace code {

class Expr: public swift::code::Stmt {
public:
  Expr(std::vector<Expr*> args = std::vector<Expr*>());
  virtual ~Expr();

  virtual std::vector<code::Expr*>& getArgs();
  virtual void clearArgs(); // only clear, will not remove the pointers

  // For Printer
  virtual void print(printer::Printer* prt) = 0;
protected:
  std::vector<Expr*> args;
};

} /* namespace code */
} /* namespace swift */
