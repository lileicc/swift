#include "NameTy.h"

#include "TypeDomain.h"

namespace swift { namespace ir {
NameTy::NameTy(TypeDomain* refer)
  :Ty(IRConstant::NAMETY), refer(refer) {
  refer->setRefer(this);
}

NameTy::~NameTy() {
}

TypeDomain* NameTy::getRefer() const {
  return refer;
}

std::string NameTy::toString() const {
  return refer->getName();
}

}
}
