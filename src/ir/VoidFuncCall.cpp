#include "VoidFuncCall.h"

namespace swift { namespace ir {
VoidFuncCall::VoidFuncCall(std::shared_ptr<FuncDefn> refer)
  :FunctionCall(refer) {
}

VoidFuncCall::~VoidFuncCall() {
}

}
}