#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class UniformIntDistrDecl: public swift::predecl::PreDecl {
public:
  UniformIntDistrDecl();
  virtual ~UniformIntDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
