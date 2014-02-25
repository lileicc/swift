#pragma once
#include "PreDeclDistr.h"

namespace swift {
namespace predecl {

class GammaDistrDecl: public swift::predecl::PreDeclDistr {
public:
  GammaDistrDecl();
  virtual ~GammaDistrDecl();

  virtual std::shared_ptr<ir::Distribution>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
