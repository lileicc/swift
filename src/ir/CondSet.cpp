#include "CondSet.h"

#include "Expr.h"
#include "VarDecl.h"
#include "IRConst.h"

namespace swift { namespace ir {

CondSet::CondSet(std::shared_ptr<VarDecl> var, std::shared_ptr<Expr> cond)
  :SetExpr(IRConstant::CONDSET), var(var) {
  if (cond)
    addArg(cond);
}

CondSet::~CondSet() {
}

const std::shared_ptr<VarDecl>& CondSet::getVar() const {
  return var;
}

std::shared_ptr<Expr> CondSet::getCond() const {
  return argSize() > 0 ? get(0) : nullptr;
}

}
}