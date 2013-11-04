#pragma once
#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class OriginRefer :
  public swift::ir::Expr {
public:
  OriginRefer(OriginAttr* refer, Expr* var);
  virtual ~OriginRefer();

  OriginAttr* getRefer();
  Expr* getVar();

private:
  Expr* var;
  OriginAttr* refer;
};

}
}