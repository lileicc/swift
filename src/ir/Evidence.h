#pragma once

#include <memory>
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class Evidence {
public:
  Evidence(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);
  virtual ~Evidence();

  const std::shared_ptr<Expr>& getLeft() const;
  const std::shared_ptr<Expr>& getRight() const;
  void print(FILE* file, int indent);

private:
  // Note: left can only be [ FunctionCall | #TypeName ]
  std::shared_ptr<Expr> left;
  // Note: right can only be non-random expression
  std::shared_ptr<Expr> right;
};

}
}
