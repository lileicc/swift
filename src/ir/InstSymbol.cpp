#include "InstSymbol.h"

#include "IRConst.h"
#include "TypeDomain.h"

namespace swift { namespace ir {
InstSymbol::InstSymbol(TypeDomain* refer, int id)
  :ConstSymbol(IRConstant::INSTANCE), refer(refer), id(id) {
}

InstSymbol::~InstSymbol() {
}

TypeDomain* InstSymbol::getRefer() const {
  return refer;
}

int InstSymbol::getID() const {
  return id;
}

bool InstSymbol::isNull() const {
  return refer == NULL;
}

}
}