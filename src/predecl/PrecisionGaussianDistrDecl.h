#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class PrecisionGaussianDistrDecl: public swift::predecl::PreDecl {
public:
  PrecisionGaussianDistrDecl();
  virtual ~PrecisionGaussianDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
