#pragma once

#include "Expr.h"
#include "IRConst.h"

namespace swift { namespace ir {

class OprExpr :
  public swift::ir::Expr {
public:
  OprExpr(IRConstant op);
  virtual ~OprExpr();

  IRConstant getOp() const;

private:
  IRConstant op;
};

}
}