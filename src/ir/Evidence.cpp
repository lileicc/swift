#include "Evidence.h"

#include "Expr.h"

namespace swift { namespace ir {

Evidence::Evidence(std::shared_ptr<Expr> left,
                   std::shared_ptr<Expr> right)
  :left(left), right(right) {
}

Evidence::~Evidence() {
}

std::shared_ptr<Expr> Evidence::getLeft() {
  return left;
}

std::shared_ptr<Expr> Evidence::getRight() {
  return right;
}
}
}