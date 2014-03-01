#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class PoissonDistrDecl: public swift::predecl::PreDecl {
public:
  PoissonDistrDecl();
  virtual ~PoissonDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
