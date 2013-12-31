/*
 * NamespaceDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Decl.h"
#include "DeclContext.h"

namespace swift {
namespace code {

class NamespaceDecl: public Decl, public DeclContext {
public:
  NamespaceDecl();
  ~NamespaceDecl();
};

} /* namespace code */
} /* namespace swift */
