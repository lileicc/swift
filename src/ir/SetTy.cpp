#include "SetTy.h"

#include "IRConst.h"

namespace swift { namespace ir {
SetTy::SetTy(Ty* refer)
  :Ty(IRConstant::SET), refer(refer) {
}

SetTy::~SetTy() {
}

Ty* SetTy::getRefer() {
  return refer;
}

std::string SetTy::toString() {
  return std::string("set<") + (refer == NULL ? "NULL" : refer->toString()) + ">";
}

}
}