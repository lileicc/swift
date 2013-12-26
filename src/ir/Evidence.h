#pragma once

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class Evidence {
public:
  Evidence(std::shared_ptr<FunctionCall> left, std::shared_ptr<ConstSymbol> right);
  virtual ~Evidence();

  const std::shared_ptr<FunctionCall>& getLeft() const;
  const std::shared_ptr<ConstSymbol>& getRight() const;

private:
  std::shared_ptr<FunctionCall> left;
  std::shared_ptr<ConstSymbol> right;
};

}
}