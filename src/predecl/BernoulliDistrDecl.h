#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class BernoulliDistrDecl: public swift::predecl::PreDecl {
public:
  BernoulliDistrDecl();
  virtual ~BernoulliDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
