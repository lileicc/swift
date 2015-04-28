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
    fprintf(file, "%*sarg%d: \n", indent + 2, "", (int)i);
    get(i)->print(file, indent + 4);
  }
}

std::string ArrayExpr::toString() {
  std::string ret = "[";
  for (size_t i = 0; i < args.size(); ++i) {
    if (i > 0) ret.push_back(',');
    ret.append(args[i]->toString());
  }
  ret.push_back(']');
  return ret;
}

}
}
