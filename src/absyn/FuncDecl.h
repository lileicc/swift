/*
 * FuncDecl.h
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#pragma once

#include <vector>

#include "Decl.h"
#include "Expr.h"
#include "Symbol.h"
#include "Ty.h"
#include "VarDecl.h"

namespace swift {
namespace absyn {

class FuncDecl: public Decl {
  bool random;
  Ty typ;
  Symbol func;
  Expr* expr;
  std::vector<VarDecl> args;

public:
  FuncDecl(int l, int c, bool random, Ty typ, Symbol func, Expr* expr);
  virtual ~FuncDecl();

  Ty& getRetTyp();
  Symbol& getFuncName();
  Expr* getExpr();
  bool isRandom();
  size_t argSize();
  void addArg(VarDecl var);
  VarDecl& getArg(int k);

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
