/*
 * Query.h
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"
#include "Stmt.h"

namespace swift {
namespace absyn {
class Query: public Stmt {
  Expr* expr;
public:
  Query(int l, int c, Expr* expr);
  virtual ~Query();

  Expr*& getExpr();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
