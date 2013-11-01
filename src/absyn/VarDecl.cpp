/*
* VarDecl.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "VarDecl.h"

namespace swift{

VarDecl::VarDecl(int l, int c, Ty typ, Symbol var)
  :Expr(l, c), typ(typ), var(var) {
}


VarDecl::~VarDecl() {
}

Ty& VarDecl::getTyp() {
  return typ;
}

Symbol& VarDecl::getVar() {
  return var;
}

// For Debugging Use
void VarDecl::print(FILE* file, int indent) {
  fprintf(file, "%*s(VarDecl: (: %s %s ) )\n", indent, "",
    typ.toString().c_str(), var.getValue().c_str());
}

}