#pragma once
#include "Expr.h"
#include "IRConst.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class QuantForm :
  public swift::ir::Expr {
public:
  QuantForm(IRConstant op);
  virtual ~QuantForm();

  void addVar(VarDecl* v);
  VarDecl* getVar();
  IRConstant getOp();
  bool isForall();
  bool isExists();

private:
  IRConstant op;
  VarDecl* var;
};

}
}