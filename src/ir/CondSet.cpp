#include "CondSet.h"

#include "Expr.h"
#include "VarDecl.h"
#include "IRConst.h"

namespace swift {
namespace ir {

CondSet::CondSet(std::shared_ptr<VarDecl> var, std::shared_ptr<Expr> func, std::shared_ptr<Expr> cond) :
    SetExpr(IRConstant::CONDSET), var(var) {
  addArg(func);
  addArg(cond);
}

CondSet::~CondSet() {
}

const std::shared_ptr<VarDecl>& CondSet::getVar() const {
  return var;
}

void CondSet::setFunc(std::shared_ptr<Expr> f) {
  args[0] = f;
}

std::shared_ptr<Expr> CondSet::getFunc() const {
  return get(0);
}

std::shared_ptr<Expr> CondSet::getCond() const {
  return get(1);
}

void CondSet::print(FILE* file, int indent) const {
  fprintf(file, "%*sCondSet:\n", indent, "");
  fprintf(file, "%*svar: %s\n", indent + 2, "", var->toString().c_str());
  if (getFunc()) {
    fprintf(file, "%*sfunc:\n", indent + 2, "");
    getFunc()->print(file, indent + 4);
  }
  if (getCond()) {
    fprintf(file, "%*scond:\n", indent + 2, "");
    getCond()->print(file, indent + 4);
  }
}

}
}
