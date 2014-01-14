#include "VarRefer.h"
#include "VarDecl.h"

namespace swift { namespace ir {
VarRefer::VarRefer(VarDecl* refer)
  :refer(refer) {
}

VarRefer::~VarRefer() {
}

VarDecl* VarRefer::getRefer() const {
  return refer;
}

}
}