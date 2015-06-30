#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class GeometricDistrDecl: public swift::predecl::PreDecl {
public:
  GeometricDistrDecl();
  virtual ~GeometricDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
