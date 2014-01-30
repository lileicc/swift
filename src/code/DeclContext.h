/*
 * DeclContext.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <vector>
#include "Decl.h"
#include "../printer/Printer.h"

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
//  virtual Decl* getMem(int k);
  virtual std::vector<Decl*>& getAllDecls();
  virtual void print(printer::Printer* prt) = 0;
private:
  std::vector<Decl*> members; // member declaration
};

} /* namespace code */
} /* namespace swift */
