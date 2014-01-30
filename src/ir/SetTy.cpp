#include "SetTy.h"

#include "IRConst.h"

namespace swift {
namespace ir {
SetTy::SetTy(const Ty* refer) :
    Ty(IRConstant::SET), refer(refer) {
}

SetTy::~SetTy() {
}

const Ty* SetTy::getRefer() const {
  return refer;
}

std::string SetTy::toString() const {
  return std::string("set<") + (refer == NULL ? "NULL" : refer->toString())
      + ">";
}

}
}
