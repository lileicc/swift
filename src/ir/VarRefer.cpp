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

void VarRefer::print(FILE* file, int indent){
  fprintf(file, "%*s(VarRefer: %s)\n", indent, "", refer->toString().c_str());
}
}
}