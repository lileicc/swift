/*
 * VarDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Decl.h"

namespace swift {
namespace code {

class VarDecl: public swift::code::Decl {
public:
  VarDecl();
  ~VarDecl();
};

} /* namespace code */
} /* namespace swift */
