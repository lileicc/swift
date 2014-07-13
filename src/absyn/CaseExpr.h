/*
 * CondSet.h
 *
 *  Created on: July 12, 2014
 *      Author: tejas
 */

#pragma once

#include "MapExpr.h"

namespace swift {
namespace absyn {
class CaseExpr: public Expr {
public:
  CaseExpr(int l, int c, Expr* test, MapExpr* m);
  virtual ~CaseExpr();

  Expr* getTest();
  MapExpr* getMap();
  
  // For Debugging Use
  void print(FILE *file, int indent);
};

}
}
