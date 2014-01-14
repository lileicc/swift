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

/**
 * DeclContext defines a context for declarations. It provides an abstract class
 * for defining an environment within which other declarations reside.
 * For example, a C++ class, and a C++ function are DeclContext.
 */
class DeclContext {
public:
  DeclContext();
  virtual ~DeclContext();
  virtual void addDecl(Decl* decl);
  Decl* getMem(int k);
  std::vector<Decl*>& getAllMem();
private:
  std::vector<Decl* > members; // member declaration
};

} /* namespace code */
} /* namespace swift */
