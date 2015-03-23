/*
 * ArrayExpr.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "ArrayExpr.h"

namespace swift {
namespace absyn {

ArrayExpr::ArrayExpr(int l, int c, int dim) :
    Expr(l, c), dim(dim) {
}

ArrayExpr::~ArrayExpr() {
}

int ArrayExpr::getDim() {
  return dim;
}

// For Debugging Use
void ArrayExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(ArrayExpr:\n", indent, "");
  fprintf(file, "%*s:dim %d\n", indent + 2, "", dim);
  fprintf(file, "%*s:args\n", indent + 2, "");
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      args[i]->print(file, indent + 4);
  fprintf(file, "%*s)\n", indent + 2, "");
  fprintf(file, "%*s)\n", indent, "");
}

std::string ArrayExpr::toString() {
  std::string ret = "[";
  for (size_t i = 0; i < args.size(); ++i) {
    if (i > 0) ret += " ,";
    if (args[i] != NULL) 
      ret += args[i]->toString();
  }
  return ret + "]";
}

Expr* ArrayExpr::clone(){
  ArrayExpr* ret = new ArrayExpr(*this);
  ret->cloneArgs();
  return ret;
}

}
}
