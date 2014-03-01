#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class GaussianDistrDecl: public swift::predecl::PreDecl {
public:
  GaussianDistrDecl();
  virtual ~GaussianDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
