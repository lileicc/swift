/*
 * DeclContext.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <vector>
#include "Decl.h"


namespace swift {
namespace code {

class DeclContext {
public:
  DeclContext();
  virtual ~DeclContext();
  virtual void addDecl(Decl* decl);
private:
  std::vector<Decl* > members; // member declaration
};

} /* namespace code */
} /* namespace swift */
