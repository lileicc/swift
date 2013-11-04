#include "Evidence.h"

#include "Expr.h"

namespace swift { namespace ir {

Evidence::Evidence(Expr* left, Expr* right)
  :left(left), right(right) {
}

Evidence::~Evidence() {
}

Expr* Evidence::getLeft() {
  return left;
}

Expr* Evidence::getRight() {
  return right;
}
}
}