/*
 * FuncApp.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "FuncApp.h"

namespace swift {
namespace absyn {

FuncApp::FuncApp(int l, int c, Symbol func) :
    Expr(l, c), func(func) {
}

FuncApp::~FuncApp() {
}

const Symbol& FuncApp::getFuncName() {
  return func;
}

// For Debugging Use
void FuncApp::print(FILE* file, int indent) {
  fprintf(file, "%*s(FuncApp:\n", indent, "");
  fprintf(file, "%*s:func %s\n", indent + 2, "", func.getValue().c_str());
  fprintf(file, "%*s(args:\n", indent + 2, "");
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      args[i]->print(file, indent + 4);
  fprintf(file, "%*s)\n", indent + 2, "");
  fprintf(file, "%*s)\n", indent, "");
}

}
}
