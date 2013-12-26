#pragma once

#include <memory>
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class Evidence {
public:
  Evidence(std::shared_ptr<Expr> left,
           std::shared_ptr<Expr> right);
  virtual ~Evidence();

  std::shared_ptr<Expr> getLeft();
  std::shared_ptr<Expr> getRight();

private:
  std::shared_ptr<Expr> left;
  std::shared_ptr<Expr> right;
};

}
}