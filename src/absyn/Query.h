/*
 * Query.h
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"
#include "Stmt.h"

#include "VarDecl.h"
#include <vector>

namespace swift {
namespace absyn {
class Query: public Stmt {
  Expr* expr;
  std::vector<VarDecl> vardecls;
  Expr* cond;

public:
  Query(int l, int c, Expr* expr);
  Query(int l, int c, Expr* expr, std::vector<VarDecl> vars);
  Query(int l, int c, Expr* expr, std::vector<VarDecl> vars, Expr* cd);
  virtual ~Query();

  Expr*& getExpr();

  Expr* getCond();
  void setCond(Expr* e);
  const VarDecl& getVarDecl(size_t i) const;
  const std::vector<VarDecl>& getVarDecls() const;

  void clear();
  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
