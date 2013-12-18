#include "Distribution.h"

namespace swift { namespace ir {

Distribution::Distribution(const std::string& distr, const predecl::PreDeclDistr* refer)
  :refer(refer), distr(distr) {
}

Distribution::~Distribution() {
}

const std::string& Distribution::getDistrName() {
  return distr;
}

const predecl::PreDeclDistr* Distribution::getRefer() {
  return refer;
}

}
}