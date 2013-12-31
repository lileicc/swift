#pragma once
#include "Expr.h"
#include "IRConst.h"
#include "IRForwardDecl.h"

#include <memory>

namespace swift { namespace ir {

class QuantForm :
  public swift::ir::Expr {
public:
  QuantForm(IRConstant op);
  virtual ~QuantForm();

  void addVar(std::shared_ptr<VarDecl> v);
  const std::shared_ptr<VarDecl>& getVar() const;
  IRConstant getOp() const;
  bool isForall() const;
  bool isExists() const;

private:
  IRConstant op;
  std::shared_ptr<VarDecl> var;
};

}
}