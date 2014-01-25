#include "VarRefer.h"
#include "VarDecl.h"

namespace swift { namespace ir {
VarRefer::VarRefer(std::shared_ptr<VarDecl> refer)
  :refer(refer) {
}

VarRefer::~VarRefer() {
}

std::shared_ptr<VarDecl> VarRefer::getRefer() const {
  return refer;
}

}
}