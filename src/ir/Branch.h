#pragma once

#include <vector>

#include "Clause.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class Branch :
  public swift::ir::Clause {
public:
  Branch();
  virtual ~Branch();

  void setVar(Expr* v);
  Expr* getVar();
  void addBranch(ConstSymbol* c, Clause* b);
  size_t size();
  ConstSymbol* getCond(int k);
  Clause* getBranch(int k);

private:
  Expr* var;
  std::vector<ConstSymbol*> cond;
  std::vector<Clause*> branch;
};

}
}