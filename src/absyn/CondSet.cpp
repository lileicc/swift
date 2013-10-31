/*
* CondSet.cpp
*
*  Created on: Oct 31, 2013
*      Author: yiwu
*/

#include "CondSet.h"

namespace swift {

CondSet::CondSet(int l, int c, VarDecl var, Expr* cond)
  :SetExpr(l, c), var(var), cond(cond) {
}

CondSet::~CondSet() {
  if (cond != NULL) delete cond;
}

VarDecl& CondSet::getVar() {
  return var;
}

Expr* CondSet::getCond() {
  return cond;
}

// For Debugging Use
void CondSet::print(FILE* file, int indent) {
  fprintf(file, "%*s(CondSet:\n", indent, "");
  fprintf(file, "%*s:var\n", indent + 2, "");
  var.print(file, indent + 4);
  if (cond != NULL) {
    fprintf(file, "%*s:cond\n", indent + 2, "");
    cond->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}