#pragma once

#include <memory>
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class Evidence {
public:
  Evidence(std::shared_ptr<Expr> left, std::shared_ptr<ConstSymbol> right);
  virtual ~Evidence();

  const std::shared_ptr<Expr>& getLeft() const;
  const std::shared_ptr<ConstSymbol>& getRight() const;

private:
  // Note: left can be [ FunctionCall | #TypeName ]
  std::shared_ptr<Expr> left;
  std::shared_ptr<ConstSymbol> right;
};

}
}