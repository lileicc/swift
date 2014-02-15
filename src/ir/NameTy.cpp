#include "NameTy.h"

#include "TypeDomain.h"

namespace swift {
namespace ir {
NameTy::NameTy(std::shared_ptr<TypeDomain> refer) :
    Ty(IRConstant::NAMETY), refer(refer) {
  refer->setType(this);
}

NameTy::~NameTy() {
}

std::shared_ptr<TypeDomain> NameTy::getRefer() const {
  return refer;
}

std::string NameTy::toString() const {
  return refer->getName();
}

}
}
