#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class DirichletDistrDecl: public swift::predecl::PreDecl {
public:
  DirichletDistrDecl();
  virtual ~DirichletDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
