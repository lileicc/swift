#include "NameTy.h"

#include "TypeDomain.h"

namespace swift { namespace ir {
NameTy::NameTy(TypeDomain* refer)
  :Ty(IRConstant::NAMETY), refer(refer) {
  refer->addRefer(this);
}

NameTy::~NameTy() {
}

TypeDomain* NameTy::getRefer() {
  return refer;
}

std::string NameTy::toString() {
  return refer->getName();
}

}
}