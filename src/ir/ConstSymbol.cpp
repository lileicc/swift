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

}
}