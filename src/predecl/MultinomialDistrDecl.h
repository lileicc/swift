#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MultinomialDistrDecl: public swift::predecl::PreDecl {
public:
  MultinomialDistrDecl();
  virtual ~MultinomialDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
