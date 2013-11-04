#include "NameTy.h"

namespace swift { namespace ir {
NameTy::NameTy(IRConstant typ, TypeDomain* refer)
  :Ty(typ), refer(refer) {
}

NameTy::~NameTy() {
}

TypeDomain* NameTy::getRefer() {
  return refer;
}

}
}