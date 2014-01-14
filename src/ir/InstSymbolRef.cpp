#include "InstSymbolRef.h"

namespace swift { namespace ir {
InstSymbolRef::InstSymbolRef(const InstSymbol* inst)
  :ConstSymbol(IRConstant::INSTANCE), inst(inst) {
}

InstSymbolRef::~InstSymbolRef() {
}

const InstSymbol* InstSymbolRef::getInst() const {
  return inst;
}

}
}
