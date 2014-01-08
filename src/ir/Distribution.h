#pragma once

#include <string>
#include <vector>

#include "Expr.h"
#include "IRForwardDecl.h"

// Forward Declaration
namespace swift { namespace predecl { class PreDeclDistr; } }

namespace swift { namespace ir {

class Distribution :
  public swift::ir::Expr {
public:
  Distribution(const std::string& name = std::string(""), const predecl::PreDeclDistr* refer = NULL);
  virtual ~Distribution();

  const predecl::PreDeclDistr* getRefer() const;
  
  const std::string& getDistrName() const;

private:
  const predecl::PreDeclDistr* refer;
  std::string name;
};

}
}