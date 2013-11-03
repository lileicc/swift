/*
 * MapExpr.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace absyn {

class MapExpr: public Expr {
public:
  MapExpr(int l, int c);
  virtual ~MapExpr();

  size_t mapSize();
  Expr* getFrom(int k);
  Expr* getTo(int k);
  void addMap(Expr* from, Expr* to);

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
