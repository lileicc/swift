#include "QuantForm.h"
#include "VarDecl.h"

namespace swift {
namespace ir {

QuantForm::QuantForm(IRConstant op) :
    op(op) {
  addArg(nullptr);
}

QuantForm::~QuantForm() {
}

void QuantForm::addVar(std::shared_ptr<VarDecl> v) {
  var = v;
}

const std::shared_ptr<VarDecl>& QuantForm::getVar() const {
  return var;
}

IRConstant QuantForm::getOp() const {
  return op;
}

bool QuantForm::isForall() const {
  return op == IRConstant::FORALL;
}

bool QuantForm::isExists() const {
  return op == IRConstant::EXISTS;
}

// Note: only may use addArg to add Condition!!
void QuantForm::addArg(std::shared_ptr<Expr> e) {
  args.resize(1);
  args[0] = e;
}

void QuantForm::setCond(std::shared_ptr<Expr> e) {
  setArgs(std::vector<std::shared_ptr<Expr> >({e}));
}

std::shared_ptr<Expr> QuantForm::getCond() const {
  return get(0);
}

void QuantForm::print(FILE* file, int indent) const {
  fprintf(file, "%*sQuantExpr:\n", indent, "");
  fprintf(file, "%*styp: %d\n", indent + 2, "", op);
  fprintf(file, "%*svar: %s\n", indent + 2, "", var->toString().c_str());
  if (get(0) != NULL) {
    fprintf(file, "%*scond:\n", indent + 2, "");
    get(0)->print(file, indent + 4);
  }
}

std::string QuantForm::toString() {
  std::string ret=(op==ir::IRConstant::FORALL ? "forall" : "exist");
  ret.append(" " + var->toString() + ": ");
  if (get(0) != NULL) ret.append(get(0)->toString());
  return ret;
}

}
}
