#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class UniformRealDistrDecl: public swift::predecl::PreDecl {
public:
  UniformRealDistrDecl();
  virtual ~UniformRealDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
