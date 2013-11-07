#pragma once

#include "IRForwardDecl.h"
#include "SetExpr.h"

namespace swift { namespace ir {

class CondSet :
  public swift::ir::SetExpr {
public:
  CondSet(VarDecl* var, std::shared_ptr<Expr> e);
  virtual ~CondSet();

  VarDecl* getVar();
  std::shared_ptr<Expr> getCond();

private:
  VarDecl* var;
};

}
}