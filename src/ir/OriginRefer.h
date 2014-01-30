#pragma once
#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class OriginRefer: public swift::ir::Expr {
public:
  OriginRefer(const OriginAttr* refer, std::shared_ptr<Expr> var);
  virtual ~OriginRefer();

  const OriginAttr* getRefer() const;
  const std::shared_ptr<Expr>& getVar() const;

private:
  const OriginAttr* refer;
  std::shared_ptr<Expr> var;
};

}
}
