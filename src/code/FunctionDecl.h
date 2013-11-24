/*
 * FunctionDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Decl.h"
#include "DeclContext.h"

namespace swift {
namespace code {

class FunctionDecl: public Decl, public DeclContext {
public:
  FunctionDecl();
  ~FunctionDecl();
};

} /* namespace code */
} /* namespace swift */
