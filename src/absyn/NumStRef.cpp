/*
* NumStRef.cpp
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#include "NumStRef.h"

namespace swift {

NumStRef::NumStRef(int l, int c, Expr* e)
  :Expr(l, c) {
  args.push_back(e);
}

NumStRef::~NumStRef() {
}

// For Debugging Use
void NumStRef::print(FILE* file, int indent) {
  fprintf(file, "%*s(NumStRef:\n", indent, "");
  if (args[0] != NULL)
    args[0]->print(file, indent + 2);
  fprintf(file, "%*s)\n", indent, "");
}

}