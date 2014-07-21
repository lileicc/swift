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

  Expr* getExp(size_t i) const;
  const std::vector<Expr*>& getExps() const;
  const VarDecl& getVarDecl(size_t i) const;
  const std::vector<VarDecl>& getVarDecls() const;
  Expr* getCond() const;
  
  // For Debugging Use
  void print(FILE *file, int indent);
  Expr* clone();

protected:
  void cloneArgs();

private:
  std::vector<VarDecl> vardecls;
  Expr* cond;
};

}
}
