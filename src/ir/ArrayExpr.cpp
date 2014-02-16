#include "ArrayExpr.h"

namespace swift {
namespace ir {

ArrayExpr::ArrayExpr() {
}

ArrayExpr::~ArrayExpr() {
}

void ArrayExpr::print(FILE* file, int indent) const {
  fprintf(file, "%*sArrayExpr:\n", indent, "");
  for (size_t i = 0; i < argSize(); i++) {
    fprintf(file, "%*sarg%lu: \n", indent + 2, "", i);
    get(i)->print(file, indent + 4);
  }
}

}
}
