#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class DiagonalMultivarGaussianDistrDecl: public swift::predecl::PreDecl {
public:
  DiagonalMultivarGaussianDistrDecl();
  virtual ~DiagonalMultivarGaussianDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
