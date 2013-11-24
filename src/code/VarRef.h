/*
 * VarRef.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace code {

class VarRef: public swift::code::Expr {
public:
  VarRef();
  ~VarRef();
};

} /* namespace code */
} /* namespace swift */
