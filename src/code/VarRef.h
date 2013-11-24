/*
 * VarRef.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include <string>
#include "Expr.h"

namespace swift {
namespace code {

class VarRef: public swift::code::Expr {
public:
  VarRef(std::string id);
  ~VarRef();
private:
  std::string id;
};

} /* namespace code */
} /* namespace swift */
