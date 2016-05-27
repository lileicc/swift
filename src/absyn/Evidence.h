/*
 * Evidence.h
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

class Evidence: public Stmt {
  Expr* left;
  Expr* right;
  std::vector<VarDecl> vardecls;
  Expr* cond;
  
public:
  Evidence(int l, int c, Expr* left, Expr* right);
  Evidence(int l, int c, Expr* left, Expr* right, std::vector<VarDecl> vars);
  Evidence(int l, int c, Expr* left, Expr* right, std::vector<VarDecl> vars, Expr* cd);
  virtual ~Evidence();

  Expr* getLeft();
  Expr* getRight();
  void setLeft(Expr* e);
  void setRight(Expr *);
  
  Expr* getCond() const;
  const VarDecl& getVarDecl(size_t i) const;
  const std::vector<VarDecl>& getVarDecls() const;

  void clear();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
