#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class BooleanDistrDecl: public swift::predecl::PreDecl {
public:
  BooleanDistrDecl();
  virtual ~BooleanDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
