#pragma once
#include "Expr.h"
#include "IRConst.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class FunctionCall :
  public swift::ir::Expr {
public:
  FunctionCall(FuncDefn* refer);
  virtual ~FunctionCall();

  IRConstant getKind();
  FuncDefn* getRefer();

private:
  IRConstant kind;
  FuncDefn* refer;
};

}
}