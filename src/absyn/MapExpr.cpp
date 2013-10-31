/*
* MapExpr.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "MapExpr.h"

namespace swift {

MapExpr::MapExpr(int l, int c)
  :Expr(l, c) {
}

MapExpr::~MapExpr() {
}

size_t MapExpr::mapSize() {
  return args.size() >> (size_t)1;
}

Expr* MapExpr::getFrom(int k) {
  return args[k << 1];
}

Expr* MapExpr::getTo(int k) {
  return args[(k << 1) | 1];
}

void MapExpr::addMap(Expr* from, Expr* to) {
  args.push_back(from);
  args.push_back(to);
}

// For Debugging Use
void MapExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(MapExpr:\n", indent, "");
  for (size_t i = 0; i < mapSize(); i++)
  {
    fprintf(file, "%*s:from#%d\n", indent + 2, "", i);
    getFrom(i)->print(file, indent + 4);
    fprintf(file, "%*s:to#%d\n", indent + 2, "", i);
    getTo(i)->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}