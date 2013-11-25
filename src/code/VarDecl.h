/*
 * VarDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include <string>
#include "Decl.h"
#include "QualType.h"
#include "DeclContext.h"

namespace swift {
namespace code {

class VarDecl: public swift::code::Decl {
public:
  VarDecl(DeclContext * context, std::string id, QualType ty);
  ~VarDecl();
protected:
  DeclContext* parent;
  std::string id;
  QualType ty;
};

} /* namespace code */
} /* namespace swift */
