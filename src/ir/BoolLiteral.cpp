#include "BoolLiteral.h"

#include "IRConst.h"

namespace swift { namespace ir {
BoolLiteral::BoolLiteral(bool v)
  :ConstSymbol(IRConstant::BOOLLITERAL), value(v) {
}

BoolLiteral::~BoolLiteral() {
}

bool BoolLiteral::getValue() {
  return value;
}

}
}