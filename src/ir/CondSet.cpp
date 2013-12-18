#include "CondSet.h"

#include "Expr.h"
#include "VarDecl.h"
#include "IRConst.h"

namespace swift { namespace ir {

CondSet::CondSet(VarDecl* var, std::shared_ptr<Expr> c)
  :SetExpr(IRConstant::CONDSET), var(var) {
  addArg(c);
}

CondSet::~CondSet() {
}

VarDecl* CondSet::getVar() {
  return var;
}

std::shared_ptr<Expr> CondSet::getCond() {
  return get(0);
}

}
}