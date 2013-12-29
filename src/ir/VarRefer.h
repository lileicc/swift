#pragma once

#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class VarRefer :
  public swift::ir::Expr {
public:
  VarRefer(VarDecl* refer = NULL);
  virtual ~VarRefer();

  VarDecl* getRefer() const;

private:
  VarDecl* refer;
};

}
}