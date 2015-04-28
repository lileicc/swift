#include "ListSet.h"

namespace swift {
namespace ir {

ListSet::ListSet() :
    SetExpr(IRConstant::LISTSET) {
}

ListSet::~ListSet() {
}

void ListSet::print(FILE* file, int indent) const {
  fprintf(file, "%*sListSet: \n", indent, "");
  for (size_t i = 0; i < argSize(); i++)
    if (get(i) != NULL)
      get(i)->print(file, indent + 2);
}

std::string ListSet::toString() {
  std::string ret = "{";
  for (size_t i = 0; i < argSize(); ++i) {
    if (i > 0) ret.push_back(',');
    if (get(i)!=nullptr)
      ret.append(get(i)->toString());
  }
  ret.push_back('}');
  return ret;
}

}
}
