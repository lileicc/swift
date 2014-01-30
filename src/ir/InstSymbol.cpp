#include "InstSymbol.h"

#include "TypeDomain.h"

namespace swift {
namespace ir {
InstSymbol::InstSymbol(std::shared_ptr<TypeDomain> refer, size_t id) :
    refer(refer), id(id) {
}

InstSymbol::~InstSymbol() {
}

std::shared_ptr<TypeDomain> InstSymbol::getRefer() const {
  return refer;
}

size_t InstSymbol::getID() const {
  return id;
}

void InstSymbol::print(FILE* file, int indent) const {
  fprintf(file, "%*s(InstSymbol: %s[%lu])\n", indent, "",
      refer->getName().c_str(), id);
}

}
}
