#pragma once

#include "IRForwardDecl.h"
#include "SetExpr.h"

#include <memory>

namespace swift {
namespace ir {

class CondSet: public swift::ir::SetExpr {
public:
  CondSet(std::shared_ptr<VarDecl> var, std::shared_ptr<Expr> func, std::shared_ptr<Expr> cond = nullptr);
  virtual ~CondSet();

  const std::shared_ptr<VarDecl>& getVar() const;
  std::shared_ptr<Expr> getFunc() const;
  void setFunc(std::shared_ptr<Expr> f);
  std::shared_ptr<Expr> getCond() const;
  void setCond(std::shared_ptr<Expr> c);

  virtual std::string toString();
  void print(FILE* file, int indent) const;

private:
  std::shared_ptr<VarDecl> var;
  int func_id, cond_id;
};

}
}
