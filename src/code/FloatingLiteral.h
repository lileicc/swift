/*
 * FloatingLiteral.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace code {

class FloatingLiteral: public swift::code::Expr {
public:
  FloatingLiteral();
  ~FloatingLiteral();
};

} /* namespace code */
} /* namespace swift */
