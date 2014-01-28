#pragma once

#include "IRForwardDecl.h"
#include "SetExpr.h"

#include <memory>

namespace swift { namespace ir {

class CondSet :
  public swift::ir::SetExpr {
public:
  CondSet(std::shared_ptr<VarDecl> var, std::shared_ptr<Expr> cond = nullptr);
  virtual ~CondSet();

  const std::shared_ptr<VarDecl>& getVar() const;
  std::shared_ptr<Expr> getCond() const;
  void print(FILE* file, int indent);

private:
  std::shared_ptr<VarDecl> var;
};

}
}