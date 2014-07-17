/*
 * MapExpr.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "MapExpr.h"

namespace swift {
namespace absyn {

MapExpr::MapExpr(int l, int c) :
    Expr(l, c) {
}

MapExpr::~MapExpr() {
}

size_t MapExpr::mapSize() {
  return args.size() >> (size_t) 1;
}

Expr* MapExpr::getFrom(size_t k) {
  return args[k << 1];
}

Expr* MapExpr::getTo(size_t k) {
  return args[(k << 1) | 1];
}

void MapExpr::addMap(Expr* from, Expr* to) {
  args.push_back(from);
  args.push_back(to);
}

// For Debugging Use
void MapExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(MapExpr:\n", indent, "");
  for (size_t i = 0; i < mapSize(); i++) {
    fprintf(file, "%*s:from#%u\n", indent + 2, "", (unsigned)i);
    getFrom(i)->print(file, indent + 4);
    fprintf(file, "%*s:to#%u\n", indent + 2, "", (unsigned)i);
    getTo(i)->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
