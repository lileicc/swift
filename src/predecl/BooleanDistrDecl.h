#pragma once
#include "PreDeclDistr.h"

namespace swift {
namespace predecl {

class BooleanDistrDecl: public swift::predecl::PreDeclDistr {
public:
  BooleanDistrDecl();
  virtual ~BooleanDistrDecl();

  virtual std::shared_ptr<ir::Distribution>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
