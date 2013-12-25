#pragma once
#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class CardExpr :
  public swift::ir::Expr {
public:
  CardExpr();
  virtual ~CardExpr();

  const Ty* getRefer() const;
  void setBody(std::shared_ptr<SetExpr> b);
  const std::shared_ptr<SetExpr>& getBody() const;

private:
  const Ty* refer;
  std::shared_ptr<SetExpr> body;
};

}
}