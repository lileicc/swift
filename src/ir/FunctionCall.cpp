#include "FunctionCall.h"

#include "FuncDefn.h"
#include "IRConst.h"

namespace swift { namespace ir {
FunctionCall::FunctionCall(std::shared_ptr<FuncDefn> refer)
  :refer(refer) {
  if (refer == NULL) kind = IRConstant::NA;
  else {
    if (refer->isRand()) kind = IRConstant::RANDOM;
    if (refer->isFixed()) kind = IRConstant::FIXED;
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

void FunctionCall::print(FILE* file, int indent){
  fprintf(file, "%*s(FunctionCall:\n", indent, "");
  fprintf(file, "%*s:calling: %s\n", indent+2, "", refer->toSignature().c_str());
  fprintf(file, "%*s(args:\n", indent+2, "");
  for(size_t i = 0; i < argSize(); i++){
    if(get(i) != nullptr){
      get(i)->print(file, indent+4);
    }
  }
  fprintf(file, "%*s)\n", indent+2, "");
  fprintf(file, "%*s)\n", indent, "");
}

}
}