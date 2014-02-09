#include "FunctionCall.h"

#include "FuncDefn.h"
#include "IRConst.h"

namespace swift {
namespace ir {
FunctionCall::FunctionCall(std::shared_ptr<FuncDefn> refer) :
    refer(refer) {
  if (refer == NULL)
    kind = IRConstant::NA;
  else {
    if (refer->isRand())
      kind = IRConstant::RANDOM;
    if (refer->isFixed())
      kind = IRConstant::FIXED;
  }
}

FunctionCall::~FunctionCall() {

}

IRConstant FunctionCall::getKind() const {
  return kind;
}

std::shared_ptr<FuncDefn> FunctionCall::getRefer() const {
  return refer;
}

void FunctionCall::print(FILE* file, int indent) const {
  fprintf(file, "%*sFunctionCall:\n", indent, "");
  fprintf(file, "%*sfun: %s\n", indent + 2, "", refer->toSignature().c_str());
  if (argSize()) {
    fprintf(file, "%*sargs:\n", indent + 2, "");
    for (size_t i = 0; i < argSize(); i++) {
      if (get(i) != nullptr) {
        get(i)->print(file, indent + 4);
      }
    }
  }
}

}
}
