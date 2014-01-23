#include "ConstSymbol.h"

namespace swift { namespace ir {
ConstSymbol::ConstSymbol(IRConstant kind)
  :kind(kind) {
}

ConstSymbol::~ConstSymbol() {
}

IRConstant ConstSymbol::getKind() const {
  return kind;
}

void ConstSymbol::print(FILE* file, int indent){
  fprintf(file, "%*s(ConstSymbol %d:\n", indent, "", kind);
  if (argSize() > 0 && get(0) != NULL){
    get(0)->print(file, indent+2);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}