/*
 * DistinctDecl.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "DistinctDecl.h"

namespace swift {
namespace absyn {
DistinctDecl::DistinctDecl(int l, int c, Symbol typ) :
    Decl(l, c), typ(typ) {
}

DistinctDecl::~DistinctDecl() {
}

void DistinctDecl::add(Symbol v, int l) {
  var.push_back(v);
  len.push_back(l);
}

size_t DistinctDecl::size() {
  return var.size();
}

const Symbol& DistinctDecl::getTyp() {
  return typ;
}

const Symbol& DistinctDecl::getVar(int k) {
  return var[k];
}

int DistinctDecl::getLen(int k) {
  return len[k];
}

// For Debugging Use
void DistinctDecl::print(FILE* file, int indent) {
  fprintf(file, "%*s(DistinctDecl:\n", indent, "");
  fprintf(file, "%*s:type %s\n", indent + 2, "", typ.getValue().c_str());
  fprintf(file, "%*s:var\n", indent + 2, "");
  for (size_t i = 0; i < var.size(); i++)
    fprintf(file, "%*s(: %s %d )\n", indent + 4, "", var[i].getValue().c_str(),
        len[i]);
  fprintf(file, "%*s)\n", indent + 2, "");
  fprintf(file, "%*s)\n", indent, "");
}

}
}
