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

}
}