/*
 * FieldDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Decl.h"

namespace swift {
namespace code {

class FieldDecl: public swift::code::Decl {
public:
  FieldDecl();
  ~FieldDecl();
};

} /* namespace code */
} /* namespace swift */
