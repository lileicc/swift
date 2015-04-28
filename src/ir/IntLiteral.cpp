#include "IntLiteral.h"

#include "IRConst.h"

namespace swift {
namespace ir {

IntLiteral::IntLiteral(int v) :
    ConstSymbol(IRConstant::INTLITERAL), value(v) {
}

IntLiteral::~IntLiteral() {
}

int IntLiteral::getValue() const {
  return value;
}

void IntLiteral::print(FILE* file, int indent) const {
  fprintf(file, "%*sIntLiteral: %d\n", indent, "", value);
}

std::string IntLiteral::toString() {
  return std::to_string(value);
}

}
}
