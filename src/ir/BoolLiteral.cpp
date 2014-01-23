#include "BoolLiteral.h"

#include "IRConst.h"

namespace swift { namespace ir {
BoolLiteral::BoolLiteral(bool v)
  :ConstSymbol(IRConstant::BOOLLITERAL), value(v) {
}

BoolLiteral::~BoolLiteral() {
}

bool BoolLiteral::getValue() const {
  return value;
}

void BoolLiteral::print(FILE* file, int indent){
  fprintf(file, "%*s(BoolLiteral: %s)\n", indent, "", (value ? "true" : "false"));
}

}
}