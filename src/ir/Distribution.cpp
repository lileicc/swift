#include "Distribution.h"

namespace swift { namespace ir {

Distribution::Distribution(const std::string& name, const predecl::PreDeclDistr* refer)
  :refer(refer), name(name) {
}

Distribution::~Distribution() {
}

const std::string& Distribution::getDistrName() {
  return name;
}

const predecl::PreDeclDistr* Distribution::getRefer() {
  return refer;
}

bool typeCheck(std::vector<std::shared_ptr<Expr>>& args) {
  return true;
}

}
}