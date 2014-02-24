#pragma once
#include "PreDeclDistr.h"

namespace swift {
namespace predecl {

class BetaDistrDecl: public swift::predecl::PreDeclDistr {
public:
  BetaDistrDecl();
  virtual ~BetaDistrDecl();

  virtual std::shared_ptr<ir::Distribution>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
