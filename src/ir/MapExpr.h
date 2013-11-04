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
  void addMap(Expr* a, Expr* b);
  Expr* getFrom(int k);
  Expr* getTo(int k);
  Ty* getFromTyp();
  Ty* getToTyp();
  void setFromTyp(Ty* t);
  void setToTyp(Ty* t);

private:
  Ty* fromTyp;
  Ty* toTyp;
};

}
}