#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class IsotropicMultivarGaussianDistrDecl: public swift::predecl::PreDecl {
public:
  IsotropicMultivarGaussianDistrDecl();
  virtual ~IsotropicMultivarGaussianDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
