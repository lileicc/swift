#include "Distribution.h"

namespace swift {
namespace ir {

Distribution::Distribution(const std::string& name,
    const predecl::PreDeclDistr* refer) :
    refer(refer), name(name) {
}

Distribution::~Distribution() {
}

const std::string& Distribution::getDistrName() const {
  return name;
}

const predecl::PreDeclDistr* Distribution::getRefer() const {
  return refer;
}

bool typeCheck(std::vector<std::shared_ptr<Expr>>& args) {
  return true;
}

void Distribution::print(FILE* file, int indent) const {
  fprintf(file, "%*s(Distribution:\n", indent, "");
  fprintf(file, "%*sname: %s\n", indent + 2, "", name.c_str());
  // todo print the args!!!
  fprintf(file, "%*s)\n", indent, "");
}

}
}
