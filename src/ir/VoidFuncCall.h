#pragma once
#include <memory>
#include "FunctionCall.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class VoidFuncCall :
  public swift::ir::FunctionCall {
public:
    VoidFuncCall(std::shared_ptr<FuncDefn> refer);
  virtual ~VoidFuncCall();
};

}
}