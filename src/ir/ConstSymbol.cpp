#include "ConstSymbol.h"

namespace swift { namespace ir {
ConstSymbol::ConstSymbol(IRConstant typ)
  :typ(typ) {
}

ConstSymbol::~ConstSymbol() {
}

IRConstant ConstSymbol::getTyp()  {
  return typ;
}

}
}