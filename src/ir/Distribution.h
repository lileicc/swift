#pragma once

#include <string>

#include "Expr.h"
#include "IRForwardDecl.h"
#include "../predecl/PreDeclDistr.h"

namespace swift { namespace ir {

class Distribution :
  public swift::ir::Expr {
public:
  Distribution(const std::string& distr = std::string(""), predecl::PreDeclDistr* refer = NULL);
  virtual ~Distribution();

  predecl::PreDeclDistr* getRefer();
  
  const std::string& getDistrName();

private:
  predecl::PreDeclDistr* refer;
  std::string distr;
};

}
}