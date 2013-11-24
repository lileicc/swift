/*
 * MethodDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "FunctionDecl.h"

namespace swift {
namespace code {

class MethodDecl: public swift::code::FunctionDecl {
public:
  MethodDecl();
  ~MethodDecl();
};

} /* namespace code */
} /* namespace swift */
