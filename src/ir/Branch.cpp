#include "Branch.h"
#include "Expr.h"

namespace swift { namespace ir {
Branch::Branch() {
}

Branch::~Branch() {
}

void Branch::setVar(std::shared_ptr<Expr> v) {
  var = v;
}

std::shared_ptr<Expr> Branch::getVar() const {
  return var;
}

void Branch::addBranch(std::shared_ptr<ConstSymbol> c, std::shared_ptr<Clause> b) {
  cond.push_back(c);
  branch.push_back(b);
}

size_t Branch::size() const {
  return branch.size();
}

std::shared_ptr<ConstSymbol> Branch::getCond(int k) const {
  return cond[k];
}

const std::vector<std::shared_ptr<ConstSymbol>>& Branch::getConds() const {
  return cond;
}

std::shared_ptr<Clause> Branch::getBranch(int k) const {
  return branch[k];
}

const std::vector<std::shared_ptr<Clause>>& Branch::getBranches() const {
  return branch;
}

}
}