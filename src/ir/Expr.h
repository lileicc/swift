/*
 * Expr.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include <vector>

#include "IRForwardDecl.h"

#include "Clause.h"
namespace swift {
namespace ir {
class Expr: public Clause {
public:
  Expr();
  virtual ~Expr();
  void addArg(Expr * expr);
  std::vector<Expr*> getArgs();
private:
  std::vector<Expr*> args;
};
}
}
