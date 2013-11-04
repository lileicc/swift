#include "Distribution.h"

#include "DistrDefn.h"

namespace swift { namespace ir {
Distribution::Distribution(DistrDefn* refer, const std::string& distr)
  :refer(refer), distr(distr) {
}

Distribution::~Distribution() {
}

const std::string& Distribution::getDistrName() {
  return distr;
}

DistrDefn* Distribution::getRefer() {
  return refer;
}

}
}