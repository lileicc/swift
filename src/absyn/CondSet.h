/*
 * CondSet.h
 *
 *  Created on: Oct 31, 2013
 *      Author: yiwu
 */

#pragma once

#include "SetExpr.h"
#include "VarDecl.h"

namespace swift {
namespace absyn {
class CondSet: public SetExpr {
public:
  CondSet(int l, int c, VarDecl var, Expr *cond = NULL);
  virtual ~CondSet();

  Expr* getCond();
  VarDecl& getVar();

  void setCond(Expr* c);

  // For Debugging Use
  void print(FILE *file, int indent);
  std::string toString();

  Expr* clone();
private:
  VarDecl var;
};

}
}
