#include "OriginRefer.h"
#include "OriginAttr.h"

namespace swift {
namespace ir {

OriginRefer::OriginRefer(const OriginAttr* refer, std::shared_ptr<Expr> var) :
    refer(refer){
      addArg(var);
}

OriginRefer::~OriginRefer() {
}

const OriginAttr* OriginRefer::getRefer() const {
  return refer;
}

std::shared_ptr<Expr> OriginRefer::getOriginArg() const {
  return get(0);
}

void OriginRefer::print(FILE* file, int indent) const {
  fprintf(file, "%*sOriginRefer:\n", indent, "");
  fprintf(file, "%*sorigin fun: %s\n", indent + 2, "", refer->getName().c_str());
  if (get(0) != nullptr) {
    fprintf(file, "%*sexpr:\n", indent + 2, "");
    get(0)->print(file, indent + 4);
  }
}

std::string OriginRefer::toString() {
  return refer->getName() + "(" + get(0)->toString() + ")";
}

}
}
