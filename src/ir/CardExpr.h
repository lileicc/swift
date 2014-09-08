#pragma once
#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class CardExpr: public swift::ir::Expr {
public:
  CardExpr();
  virtual ~CardExpr();

  const Ty* getType() const;
  void setBody(std::shared_ptr<SetExpr> b);
  std::shared_ptr<SetExpr> getBody() const;
  void print(FILE* file, int indent) const;

private:
  const Ty* referTyp;
  std::shared_ptr<SetExpr> body;
};

}
}
