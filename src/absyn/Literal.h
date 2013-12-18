/*
 * Literal.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace absyn {

class Literal: public Expr {
public:
  Literal(int l, int c);
  virtual ~Literal();
};

}
}
