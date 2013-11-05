/*
 * FuncDecl.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "FuncDecl.h"

namespace swift {
namespace absyn {

FuncDecl::FuncDecl(int l, int c, bool random, Ty typ, Symbol func, Expr* expr) :
    Decl(l, c), random(random), typ(typ), func(func), expr(expr) {
}

FuncDecl::~FuncDecl() {
  if (expr != NULL)
    delete expr;
}

const Ty& FuncDecl::getRetTyp() {
  return typ;
}

const Symbol& FuncDecl::getFuncName() {
  return func;
}

bool FuncDecl::isRandom() {
  return random;
}

Expr* FuncDecl::getExpr() {
  return expr;
}

size_t FuncDecl::argSize() {
  return args.size();
}

const VarDecl& FuncDecl::getArg(int k) {
  return args[k];
}

void FuncDecl::addArg(VarDecl var) {
  args.push_back(var);
}

// For Debugging Use
void FuncDecl::print(FILE* file, int indent) {
  fprintf(file, "%*s(FuncDecl:\n", indent, "");
  fprintf(file, "%*s:kind %s\n", indent + 2, "", (random ? "random" : "fixed"));
  fprintf(file, "%*s:type %s\n", indent + 2, "", typ.toString().c_str());
  fprintf(file, "%*s:func %s\n", indent + 2, "", func.getValue().c_str());
  if (args.size() > 0) {
    fprintf(file, "%*s(args:\n", indent + 2, "");
    for (size_t i = 0; i < args.size(); i++)
      args[i].print(file, indent + 4);
    fprintf(file, "%*s)\n", indent + 2, "");
  }
  if (expr != NULL) {
    fprintf(file, "%*sexpr:\n", indent + 2, "");
    expr->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
