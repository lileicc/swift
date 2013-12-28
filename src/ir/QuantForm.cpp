#include "QuantForm.h"

namespace swift { namespace ir {

QuantForm::QuantForm(IRConstant op)
  :op(op) {
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

}
}