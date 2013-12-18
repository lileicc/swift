#pragma once

#include <string>

#include "Expr.h"
#include "IRForwardDecl.h"
#include "../predecl/PreDeclDistr.h"

namespace swift { namespace ir {

class Distribution :
  public swift::ir::Expr {
public:
  Distribution(const std::string& distr = std::string(""), const predecl::PreDeclDistr* refer = NULL);
  virtual ~Distribution();

  const predecl::PreDeclDistr* getRefer();
  
  const std::string& getDistrName();

private:
  const predecl::PreDeclDistr* refer;
  std::string distr;
};

}
}