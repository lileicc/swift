/*
 * CondSet.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: yiwu
 */

#include "CondSet.h"

namespace swift {
namespace absyn {
CondSet::CondSet(int l, int c, VarDecl var, Expr* cond) :
    SetExpr(l, c), var(var) {
  if (cond != nullptr)
    this->add(cond);
}

CondSet::~CondSet() {
}

VarDecl& CondSet::getVar() {
  return var;
}

Expr* CondSet::getCond() {
  return size() > 0 ? get(0) : nullptr;
}

void CondSet::setCond(Expr* c) {
  if (args.size() < 1) args.push_back(c);
  else args[0] = c;
}

// For Debugging Use
void CondSet::print(FILE* file, int indent) {
  fprintf(file, "%*s(CondSet:\n", indent, "");
  fprintf(file, "%*s:var\n", indent + 2, "");
  var.print(file, indent + 4);
  if (getCond() != NULL) {
    fprintf(file, "%*s:cond\n", indent + 2, "");
    getCond()->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
