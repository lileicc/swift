#include "CondSet.h"

#include "Expr.h"
#include "VarDecl.h"
#include "IRConst.h"

namespace swift { namespace ir {

CondSet::CondSet(VarDecl* var, Expr* c)
  :SetExpr(IRConstant::CONDSET), var(var) {
  addArg(c);
}

CondSet::~CondSet() {
}

VarDecl* CondSet::getVar() {
  return var;
}

Expr* CondSet::getCond() {
  return get(0);
}

}
}