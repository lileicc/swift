#include "VarRefer.h"
#include "VarDecl.h"

namespace swift {
namespace ir {
VarRefer::VarRefer(std::shared_ptr<VarDecl> refer) :
    refer(refer) {
}

VarRefer::~VarRefer() {
}

std::shared_ptr<VarDecl> VarRefer::getRefer() const {
  return refer;
}

void VarRefer::print(FILE* file, int indent) const {
  fprintf(file, "%*s(VarRefer: %s)\n", indent, "", refer->toString().c_str());
}
}
}
