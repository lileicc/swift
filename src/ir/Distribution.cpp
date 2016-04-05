#include "Distribution.h"
#include "Ty.h"

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
  fprintf(file, "%*sDistribution: retType = %s\n", indent, "", getTyp()->toString().c_str());
  fprintf(file, "%*sname: %s\n", indent + 2, "", name.c_str());
  if (argSize()) {
    fprintf(file, "%*sargs:\n", indent + 2, "");
    for (size_t i = 0; i < argSize(); i++) {
      if (get(i) != nullptr) {
        get(i)->print(file, indent + 4);
      }
    }
  }
}

std::string Distribution::toString() {
  std::string ret = name + "(";
  for (size_t i = 0; i < argSize(); ++i) {
    if (i > 0) ret.push_back(',');
    if (get(i) != nullptr)
      ret.append(get(i)->toString());
  }
  ret.push_back(')');
  return ret;
}

}
}
