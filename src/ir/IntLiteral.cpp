#include "IntLiteral.h"

#include "IRConst.h"

namespace swift { namespace ir {

IntLiteral::IntLiteral(int v)
  :ConstSymbol(IRConstant::INTLITERAL), value(v) {
}

IntLiteral::~IntLiteral() {
}

int IntLiteral::getValue() {
  return value;
}

}
}