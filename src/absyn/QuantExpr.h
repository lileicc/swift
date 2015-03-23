/*
 * QuantExpr.h
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"
#include "Symbol.h"
#include "VarDecl.h"

namespace swift {
namespace absyn {

class QuantExpr: public Expr {
  AbsynConstant typ;
  VarDecl var;
public:
  QuantExpr(int l, int c, AbsynConstant typ, VarDecl var, Expr* cond);
  virtual ~QuantExpr();

  AbsynConstant getTyp();
  const VarDecl& getVar();
  Expr* getCond();

  // For Debugging Use
  void print(FILE* file, int indent);
  std::string toString();

  Expr* clone();
};

}
}
