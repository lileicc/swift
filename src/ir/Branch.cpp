#include "Branch.h"
#include "Expr.h"

namespace swift { namespace ir {
Branch::Branch() {
}

Branch::~Branch() {
}

void Branch::setVar(Expr* v) {
  var = v;
}

Expr* Branch::getVar() {
  return var;
}

void Branch::addBranch(ConstSymbol* c, Clause* b) {
  cond.push_back(c);
  branch.push_back(b);
}

size_t Branch::size() {
  return branch.size();
}

ConstSymbol* Branch::getCond(int k) {
  return cond[k];
}

Clause* Branch::getBranch(int k) {
  return branch[k];
}

}
}