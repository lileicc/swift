#pragma once

#include "Expr.h"
#include "IRConst.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class ConstSymbol :
  public swift::ir::Expr {
public:
  ConstSymbol(IRConstant typ);
  virtual ~ConstSymbol();

  IRConstant getKind() const;

private:
  IRConstant kind;
};

}
}