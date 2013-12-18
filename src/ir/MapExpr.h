#pragma once
#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class MapExpr :
  public swift::ir::Expr {
public:
  MapExpr();
  virtual ~MapExpr();

  size_t mapSize();
  void addMap(std::shared_ptr<Expr> a, std::shared_ptr<Expr> b);
  std::shared_ptr<Expr> getFrom(int k);
  std::shared_ptr<Expr> getTo(int k);
  const Ty* getFromTyp();
  const Ty* getToTyp();
  void setFromTyp(const Ty* t);
  void setToTyp(const Ty* t);

private:
  const Ty* fromTyp;
  const Ty* toTyp;
};

}
}