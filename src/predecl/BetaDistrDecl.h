#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class BetaDistrDecl: public swift::predecl::PreDecl {
public:
  BetaDistrDecl();
  virtual ~BetaDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
