/*
 * Expr.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include <vector>

#include "Clause.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {
class Expr: public Clause {
public:
  Expr();
  virtual ~Expr();
  void addArg(std::shared_ptr<Expr> expr);
  void setArgs(std::vector<std::shared_ptr<Expr>> a);
  const std::vector<std::shared_ptr<Expr>>& getArgs();
  std::shared_ptr<Expr> get(int k);
  size_t argSize();
private:
  std::vector<std::shared_ptr<Expr>> args;
};
}
}
