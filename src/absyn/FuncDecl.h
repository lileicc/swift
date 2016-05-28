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
  bool random, is_extern;
  Ty typ;
  Symbol func;
  Expr* expr;
  std::vector<VarDecl> args;

public:
  FuncDecl(int l, int c, bool random, Ty typ, Symbol func, Expr* expr);
  FuncDecl(int l, int c, Ty typ, Symbol func); // declaration for external function
  virtual ~FuncDecl();

  const Ty& getRetTyp() const;
  const Symbol& getFuncName() const;
  Expr*& getExpr();
  bool isRandom() const;
  bool isExtern() const;
  size_t argSize() const;
  void addArg(VarDecl var);
  const VarDecl& getArg(int k) const;
  const std::vector<VarDecl>& getArgs() const;

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
