#include "InstSymbol.h"

#include "TypeDomain.h"

namespace swift { namespace ir {
InstSymbol::InstSymbol(TypeDomain* refer, int id)
  :refer(refer), id(id) {
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
