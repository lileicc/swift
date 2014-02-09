#include "QuantForm.h"
#include "VarDecl.h"

namespace swift {
namespace ir {

QuantForm::QuantForm(IRConstant op) :
    op(op) {
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

void QuantForm::print(FILE* file, int indent) const {
  fprintf(file, "%*sQuantExpr:\n", indent, "");
  fprintf(file, "%*styp: %d\n", indent + 2, "", op);
  fprintf(file, "%*svar: %s\n", indent + 2, "", var->toString().c_str());
  if (get(0) != NULL) {
    fprintf(file, "%*scond:\n", indent + 2, "");
    get(0)->print(file, indent + 4);
  }
}

}
}
