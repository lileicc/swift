/*
 * IntegerLiteral.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace code {

class IntegerLiteral: public swift::code::Expr {
public:
  IntegerLiteral();
  ~IntegerLiteral();
};

} /* namespace code */
} /* namespace swift */
