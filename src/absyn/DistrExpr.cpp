/*
 * DistrExpr.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "DistrExpr.h"

namespace swift {
namespace absyn {

DistrExpr::DistrExpr(int l, int r, Symbol distr) :
    Expr(l, r), distr(distr) {
}

DistrExpr::~DistrExpr() {
}

const Symbol& DistrExpr::getDistrName() {
  return distr;
}

// For Debugging Use
void DistrExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(DistrExpr:\n", indent, "");
  fprintf(file, "%*s:distr %s\n", indent + 2, "", distr.getValue().c_str());
  fprintf(file, "%*s(args:\n", indent + 2, "");
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      args[i]->print(file, indent + 4);
  fprintf(file, "%*s)\n", indent + 2, "");
  fprintf(file, "%*s)\n", indent, "");
}

}
}
