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

void IntLiteral::print(FILE* file, int indent){
  fprintf(file, "%*sIntLiteral: %d", indent, "", value);
}

}
}
