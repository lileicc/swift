#include "TimestepLiteral.h"

#include "IRConst.h"

namespace swift {
namespace ir {

TimestepLiteral::TimestepLiteral(unsigned v) :
    ConstSymbol(IRConstant::TIMESTEP), value(v) {
}

TimestepLiteral::~TimestepLiteral() {
}

unsigned TimestepLiteral::getValue() const {
  return value;
}

void TimestepLiteral::print(FILE* file, int indent) const {
  fprintf(file, "%*sTimestepLiteral: %u\n", indent, "", value);
}

std::string TimestepLiteral::toString() {
  return "@" + std::to_string(value);
}

}
}
