#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class DiagGaussianDistrDecl: public swift::predecl::PreDecl {
public:
  DiagGaussianDistrDecl();
  virtual ~DiagGaussianDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
