/*
 * CardinalityExpr.h
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace absyn {

class CardinalityExpr: public Expr {
public:
  CardinalityExpr(int l, int c, Expr* e);
  virtual ~CardinalityExpr();

  // For Debugging Use
  void print(FILE* file, int indent);

  Expr* clone();
};

}
}
