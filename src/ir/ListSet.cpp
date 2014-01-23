#include "ListSet.h"

namespace swift { namespace ir {

ListSet::ListSet()
  :SetExpr(IRConstant::LISTSET) {
}

ListSet::~ListSet() {
}

void ListSet::print(FILE* file, int indent) {
  fprintf(file, "%*s(ListSet: (:\n", indent, "");
  for (size_t i = 0; i < argSize(); i++)
    if (get(i) != NULL)
      get(i)->print(file, indent + 2);
  fprintf(file, "%*s) )\n", indent, "");
}

}
}