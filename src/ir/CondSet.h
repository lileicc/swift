#pragma once

#include "IRForwardDecl.h"
#include "SetExpr.h"

namespace swift { namespace ir {

class CondSet :
  public swift::ir::SetExpr {
public:
  CondSet(VarDecl* var, Expr* e);
  virtual ~CondSet();

  VarDecl* getVar();
  Expr* getCond();

private:
  VarDecl* var;
};

}
}