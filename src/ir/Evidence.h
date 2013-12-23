#pragma once

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class Evidence {
public:
  Evidence(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);
  virtual ~Evidence();

  const std::shared_ptr<Expr>& getLeft() const;
  const std::shared_ptr<Expr>& getRight() const;

private:
  std::shared_ptr<Expr> left;
  std::shared_ptr<Expr> right;
};

}
}