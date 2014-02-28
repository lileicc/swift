#include "Distribution.h"

namespace swift {
namespace ir {

Distribution::Distribution(const std::string& name,
    const predecl::PreDecl* refer) :
    refer(refer), name(name), arg_rand(false) {
}

Distribution::~Distribution() {
}

bool Distribution::isArgRandom() const {
  return arg_rand;
}

void Distribution::processArgRandomness() {
  for (auto a : args) {
    if (a->isRandom())
      arg_rand = true;
  }
}

const std::string& Distribution::getDistrName() const {
  return name;
}

const predecl::PreDecl* Distribution::getRefer() const {
  return refer;
}

bool typeCheck(std::vector<std::shared_ptr<Expr>>& args) {
  return true;
}

void Distribution::print(FILE* file, int indent) const {
  fprintf(file, "%*sDistribution:\n", indent, "");
  fprintf(file, "%*sname: %s\n", indent + 2, "", name.c_str());
  // todo print the args!!!
}

}
}
