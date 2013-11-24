/*
 * NamespaceDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Decl.h"

namespace swift {
namespace code {

class NamespaceDecl: public swift::code::Decl {
public:
  NamespaceDecl();
  ~NamespaceDecl();
};

} /* namespace code */
} /* namespace swift */
