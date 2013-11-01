/*
* ListSet.cpp
*
*  Created on: Oct 31, 2013
*      Author: yiwu
*/

#include "ListSet.h"

namespace swift {

ListSet::ListSet(int l, int c)
  :SetExpr(l, c) {
}

ListSet::~ListSet() {
}

// For Debugging Use
void ListSet::print(FILE* file, int indent) {
  fprintf(file, "%*s(ListSet: (:\n", indent, "");
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      args[i]->print(file, indent + 2);
  fprintf(file, "%*s) )\n", indent, "");
}

}