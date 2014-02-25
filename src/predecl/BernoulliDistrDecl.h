#pragma once
#include "PreDeclDistr.h"

namespace swift {
namespace predecl {

class BernoulliDistrDecl: public swift::predecl::PreDeclDistr {
public:
  BernoulliDistrDecl();
  virtual ~BernoulliDistrDecl();

  virtual std::shared_ptr<ir::Distribution>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
