/*
 * BinaryOperator.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace code {

class BinaryOperator: public swift::code::Expr {
public:
  BinaryOperator();
  ~BinaryOperator();
};

} /* namespace code */
} /* namespace swift */
