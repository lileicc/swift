#include "Evidence.h"

#include "Expr.h"
#include "ConstSymbol.h"

namespace swift {
namespace ir {

Evidence::Evidence(std::shared_ptr<Expr> left,
    std::shared_ptr<ConstSymbol> right) :
    left(left), right(right) {
}

Evidence::~Evidence() {
}

const std::shared_ptr<Expr>& Evidence::getLeft() const {
  return left;
}

const std::shared_ptr<ConstSymbol>& Evidence::getRight() const {
  return right;
}

void Evidence::print(FILE* file, int indent) {
  fprintf(file, "%*sEvidence:\n", indent, "");
  if (getLeft() != nullptr) {
    fprintf(file, "%*sleft:\n", indent + 2, "");
    getLeft()->print(file, indent + 4);
  }
  if (getRight() != nullptr) {
    fprintf(file, "%*sright:\n", indent + 2, "");
    getRight()->print(file, indent + 4);
  }
}

}
}
