/*
 * TupleSetExpr.h
 *
 *  Created on: July 12, 2014
 *      Author: tejas
 */

#pragma once

#include "SetExpr.h"
#include "VarDecl.h"
#include <vector>

namespace swift {
namespace absyn {
class TupleSetExpr: public SetExpr {
public:
  TupleSetExpr(int l, int c, std::vector<Expr*> exps, std::vector<VarDecl> vardecls, Expr* cond);
  virtual ~TupleSetExpr();

  Expr* getExp(size_t i);
  const std::vector<VarDecl>& getVarDecls();
  Expr* getCond();
  
  // For Debugging Use
  void print(FILE *file, int indent);
private:
  std::vector<VarDecl> vardecls;
};

}
}
