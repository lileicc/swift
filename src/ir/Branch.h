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

  void setVar(std::shared_ptr<Expr> v);
  std::shared_ptr<Expr> getVar() const ;
  void addBranch(std::shared_ptr<ConstSymbol> c, std::shared_ptr<Clause> b);
  size_t size() const ;
  std::shared_ptr<ConstSymbol> getCond(int k) const;
  const std::vector<std::shared_ptr<ConstSymbol>>& getConds() const;
  std::shared_ptr<Clause> getBranch(int k) const ;
  const std::vector<std::shared_ptr<Clause>>& getBranches() const ;

private:
  std::shared_ptr<Expr> var;
  std::vector<std::shared_ptr<ConstSymbol>> cond;
  std::vector<std::shared_ptr<Clause>> branch;
};

}
}