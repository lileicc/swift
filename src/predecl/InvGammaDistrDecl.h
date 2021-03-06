#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class InvGammaDistrDecl: public swift::predecl::PreDecl {
public:
  InvGammaDistrDecl();
  virtual ~InvGammaDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
