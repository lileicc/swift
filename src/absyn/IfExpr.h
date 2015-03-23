/*
 * IfExpr.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace absyn {

class IfExpr: public Expr {
public:
  IfExpr(int l, int c, Expr* cond, Expr* then_clause, Expr* else_clause = NULL);
  virtual ~IfExpr();

  Expr* getCond();
  Expr* getThen();
  Expr* getElse();

  // For Debugging Use
  void print(FILE* file, int indent);
  std::string toString();

  Expr* clone();
};

}
} /* namespace swift */
