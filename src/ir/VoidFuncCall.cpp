#include "VoidFuncCall.h"

namespace swift { namespace ir {
VoidFuncCall::VoidFuncCall(FuncDefn* refer)
  :FunctionCall(refer) {
}

VoidFuncCall::~VoidFuncCall() {
}

}
}