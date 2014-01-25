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

}
}