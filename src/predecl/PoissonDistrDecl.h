#pragma once
#include "PreDeclDistr.h"

namespace swift {
namespace predecl {

class PoissonDistrDecl: public swift::predecl::PreDeclDistr {
public:
  PoissonDistrDecl();
  virtual ~PoissonDistrDecl();

  virtual std::shared_ptr<ir::Distribution>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
