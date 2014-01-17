#include "InstSymbol.h"

#include "TypeDomain.h"

namespace swift { namespace ir {
InstSymbol::InstSymbol(TypeDomain* refer, size_t id)
  :refer(refer), id(id) {
}

InstSymbol::~InstSymbol() {
}

TypeDomain* InstSymbol::getRefer() const {
  return refer;
}

size_t InstSymbol::getID() const {
  return id;
}

}
}
