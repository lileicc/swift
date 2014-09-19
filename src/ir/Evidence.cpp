#include "Evidence.h"

#include "Expr.h"
#include "ConstSymbol.h"
#include "Ty.h"

namespace swift {
namespace ir {

Evidence::Evidence(std::shared_ptr<Expr> left,
    std::shared_ptr<Expr> right) :
    left(left), right(right) {
}

Evidence::~Evidence() {
}

const std::shared_ptr<Expr>& Evidence::getLeft() const {
  return left;
}

const std::shared_ptr<Expr>& Evidence::getRight() const {
  return right;
}

void Evidence::print(FILE* file, int indent) {
  fprintf(file, "%*sEvidence:\n", indent, "");
  if (getLeft() != nullptr) {
    fprintf(file, "%*sleft: type = %s\n", indent + 2, "", getLeft()->getTyp()->toString().c_str());
    getLeft()->print(file, indent + 4);
  }
  if (getRight() != nullptr) {
    fprintf(file, "%*sright: type = %s\n", indent + 2, "", getRight()->getTyp()->toString().c_str());
    getRight()->print(file, indent + 4);
  }
}

}
}
