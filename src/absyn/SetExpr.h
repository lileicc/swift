/*
 * SetExpr.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"
#include "Symbol.h"

namespace swift {
namespace absyn {

class SetExpr: public Expr {
public:
  SetExpr(int l, int c);
  virtual ~SetExpr();
};

}
}
