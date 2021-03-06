#include "BoolLiteral.h"

#include "IRConst.h"

namespace swift {
namespace ir {
BoolLiteral::BoolLiteral(bool v) :
    ConstSymbol(IRConstant::BOOLLITERAL), value(v) {
}

BoolLiteral::~BoolLiteral() {
}

bool BoolLiteral::getValue() const {
  return value;
}

void BoolLiteral::print(FILE* file, int indent) const {
  fprintf(file, "%*sBoolLiteral: %s\n", indent, "",
      (value ? "true" : "false"));
}

std::string BoolLiteral::toString() {
  return value ? "'true" : "'false";
}

}
}
