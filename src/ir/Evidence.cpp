#include "Evidence.h"

#include "Expr.h"

namespace swift { namespace ir {

Evidence::Evidence(std::shared_ptr<Expr> left, std::shared_ptr<ConstSymbol> right)
  :left(left), right(right) {
}

Evidence::~Evidence() {
}

const std::shared_ptr<Expr>& Evidence::getLeft() const {
  return left;
}

const std::shared_ptr<ConstSymbol>& Evidence::getRight() const {
  return right;
}
}
}