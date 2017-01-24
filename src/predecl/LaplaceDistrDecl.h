#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class LaplaceDistrDecl: public swift::predecl::PreDecl {
public:
  LaplaceDistrDecl();
  virtual ~LaplaceDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
