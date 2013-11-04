#pragma once

#include <string>

#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class Distribution :
  public swift::ir::Expr {
public:
  Distribution(DistrDefn* refer, const std::string& distr = std::string(""));
  virtual ~Distribution();

  DistrDefn* getRefer();
  
  // For Debugging Use
  const std::string& getDistrName();

private:
  DistrDefn* refer;
  // For Debugging Use
  std::string distr;
};

}
}