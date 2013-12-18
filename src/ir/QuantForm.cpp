#include "QuantForm.h"

namespace swift { namespace ir {

QuantForm::QuantForm(IRConstant op)
  :op(op) {
}

QuantForm::~QuantForm() {
}

void QuantForm::addVar(VarDecl* v) {
  var = v;
}

VarDecl* QuantForm::getVar() {
  return var;
}

IRConstant QuantForm::getOp() {
  return op;
}

bool QuantForm::isForall() {
  return op == IRConstant::FORALL;
}

bool QuantForm::isExists() {
  return op == IRConstant::EXISTS;
}

}
}