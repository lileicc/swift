/*
 * OriginDecl.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "OriginDecl.h"

namespace swift {
namespace absyn {

OriginDecl::OriginDecl(int l, int c, Symbol typ, Symbol func, Symbol arg) :
    Decl(l, c), typ(typ), func(func), arg(arg) {
}

OriginDecl::~OriginDecl() {
}

Symbol& OriginDecl::getArg() {
  return arg;
}

Symbol& OriginDecl::getFunc() {
  return func;
}

Symbol& OriginDecl::getTyp() {
  return typ;
}

// For Debugging Use
void OriginDecl::print(FILE* file, int indent) {
  fprintf(file, "%*s(OriginDecl:\n", indent, "");
  fprintf(file, "%*s:func %s\n", indent + 2, "", func.getValue().c_str());
  fprintf(file, "%*s:typ %s\n", indent + 2, "", typ.getValue().c_str());
  fprintf(file, "%*s:arg %s\n", indent + 2, "", arg.getValue().c_str());
  fprintf(file, "%*s)\n", indent, "");
}

}
}
