#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MultivarGaussianDistrDecl: public swift::predecl::PreDecl {
public:
  MultivarGaussianDistrDecl();
  virtual ~MultivarGaussianDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
