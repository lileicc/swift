/*
 * ClassDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Decl.h"

namespace swift {
namespace code {

class ClassDecl: public swift::code::Decl {
public:
  ClassDecl();
  ~ClassDecl();
};

} /* namespace code */
} /* namespace swift */
