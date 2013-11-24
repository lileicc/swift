/*
 * ParamVarDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "VarDecl.h"

namespace swift {
namespace code {

class ParamVarDecl: public swift::code::VarDecl {
public:
  ParamVarDecl();
  ~ParamVarDecl();
};

} /* namespace code */
} /* namespace swift */
