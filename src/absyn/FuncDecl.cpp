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
    Decl(l, c), random(random), is_extern(false), typ(typ), func(func), expr(expr) {
}

FuncDecl::FuncDecl(int l, int c, Ty typ, Symbol func) :
    Decl(l, c), random(false), is_extern(true), typ(typ), func(func), expr(NULL) {
}

FuncDecl::~FuncDecl() {
  if (expr != NULL)
    delete expr;
}

const Ty& FuncDecl::getRetTyp() const {
  return typ;
}

const Symbol& FuncDecl::getFuncName() const {
  return func;
}

bool FuncDecl::isRandom() const {
  return random;
}

bool FuncDecl::isExtern() const {
  return is_extern;
}

Expr*& FuncDecl::getExpr() {
  return expr;
}

size_t FuncDecl::argSize() const {
  return args.size();
}

const VarDecl& FuncDecl::getArg(int k) const {
  return args[k];
}

void FuncDecl::addArg(VarDecl var) {
  args.push_back(var);
}

// For Debugging Use
void FuncDecl::print(FILE* file, int indent) {
  fprintf(file, "%*s(FuncDecl:\n", indent, "");
  fprintf(file, "%*s:kind %s\n", indent + 2, "", (random ? "random" : (is_extern ? "extern" : "fixed")));
  fprintf(file, "%*s:type %s\n", indent + 2, "", typ.toString().c_str());
  fprintf(file, "%*s:func %s\n", indent + 2, "", func.getValue().c_str());
  if (args.size() > 0) {
    fprintf(file, "%*s:args\n", indent + 2, "");
    for (size_t i = 0; i < args.size(); i++)
      args[i].print(file, indent + 4);
  }
  if (expr != NULL) {
    fprintf(file, "%*s:expr\n", indent + 2, "");
    expr->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
