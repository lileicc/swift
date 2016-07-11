#include "CondSet.h"

#include "Expr.h"
#include "VarDecl.h"
#include "IRConst.h"

namespace swift {
namespace ir {

CondSet::CondSet(std::shared_ptr<VarDecl> var, std::shared_ptr<Expr> func, std::shared_ptr<Expr> cond) :
    SetExpr(IRConstant::CONDSET), var(var) {
  if (func != nullptr) {
    func_id = (int) args.size();
    addArg(func);
  } else
    func_id = -1;
  if (cond != nullptr) {
    cond_id = (int) args.size();
    addArg(cond);
  } else
    cond_id = -1;
}

CondSet::~CondSet() {
}

const std::shared_ptr<VarDecl>& CondSet::getVar() const {
  return var;
}

void CondSet::setFunc(std::shared_ptr<Expr> f) {
  if (func_id > -1)
    args[func_id] = f;
  else {
    func_id = (int) args.size();
    args.push_back(f);
  }
}

void CondSet::setCond(std::shared_ptr<Expr> c) {
  if (cond_id > -1)
    args[cond_id] = c;
  else {
    cond_id = (int) args.size();
    args.push_back(c);
  }
}

std::shared_ptr<Expr> CondSet::getFunc() const {
  return (func_id < 0 ? nullptr : args[func_id]);
}

std::shared_ptr<Expr> CondSet::getCond() const {
  return (cond_id < 0 ? nullptr : args[cond_id]);
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

std::string CondSet::toString() {
  std::string ret = "{"+var->toString();
  if (getFunc())
    ret.append(" : "+getFunc()->toString());
  if (getCond()) {
    ret.append(" on " + getCond()->toString());
  }
  return ret + "}";
}

}
}
