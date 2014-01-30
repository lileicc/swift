#include "DoubleLiteral.h"

#include "IRConst.h"

namespace swift {
namespace ir {

DoubleLiteral::DoubleLiteral(double v) :
    ConstSymbol(IRConstant::DOUBLELITERAL), value(v) {
}

DoubleLiteral::~DoubleLiteral() {
}

double DoubleLiteral::getValue() const {
  return value;
}

void DoubleLiteral::print(FILE* file, int indent) const {
  fprintf(file, "%*s(DoubleLiteral: %f )\n", indent, "", value);
}

}
}
