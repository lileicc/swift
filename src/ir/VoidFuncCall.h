#pragma once
#include "FunctionCall.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class VoidFuncCall :
  public swift::ir::FunctionCall {
public:
  VoidFuncCall(FuncDefn* refer);
  virtual ~VoidFuncCall();
};

}
}