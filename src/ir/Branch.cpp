#include "Branch.h"
#include "Expr.h"
#include "ConstSymbol.h"

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

std::shared_ptr<ConstSymbol> Branch::getCond(size_t k) const {
  return cond[k];
}

const std::vector<std::shared_ptr<ConstSymbol>>& Branch::getConds() const {
  return cond;
}

std::shared_ptr<Clause> Branch::getBranch(size_t k) const {
  return branch[k];
}

const std::vector<std::shared_ptr<Clause>>& Branch::getBranches() const {
  return branch;
}

void Branch::print(FILE* file, int indent){
  fprintf(file, "%*s(Branch:\n", indent, "");
  fprintf(file, "%*svar:\n", indent+2, "");
  getVar()->print(file, indent+2);
  for(size_t i = 0; i < size(); i++){
    fprintf(file, "%*scond %d: %d\n", indent+2, "", i, getCond(i)->getKind());
    fprintf(file, "%*sbranch %d:\n", indent+2, "", i);
    getBranch(i)->print(file, indent+4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}