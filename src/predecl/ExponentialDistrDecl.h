#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class ExponentialDistrDecl: public swift::predecl::PreDecl {
public:
  ExponentialDistrDecl();
  virtual ~ExponentialDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
