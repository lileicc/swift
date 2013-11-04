#pragma once
#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class CardExpr :
  public swift::ir::Expr {
public:
  CardExpr();
  virtual ~CardExpr();

  void setRefer(Ty* t);
  Ty* getRefer();

private:
  Ty* refer;
};

}
}