/*
 * FunctionDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Decl.h"

namespace swift {
namespace code {

class FunctionDecl: public swift::code::Decl {
public:
  FunctionDecl();
  ~FunctionDecl();
};

} /* namespace code */
} /* namespace swift */
