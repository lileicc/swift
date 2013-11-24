/*
 * DeclContext.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <vector>
#include <memory>
#include "Decl.h"


namespace swift {
namespace code {

class DeclContext {
public:
  DeclContext();
  virtual ~DeclContext();
  virtual void addDecl(std::shared_ptr<Decl> decl);
private:
  std::vector<std::shared_ptr<Decl> > members; // member declaration
};

} /* namespace code */
} /* namespace swift */
