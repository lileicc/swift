#pragma once
#include "PreDeclDistr.h"

namespace swift {
namespace predecl {

class GaussianDistrDecl: public swift::predecl::PreDeclDistr {
public:
  GaussianDistrDecl();
  virtual ~GaussianDistrDecl();

  virtual std::shared_ptr<ir::Distribution>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
