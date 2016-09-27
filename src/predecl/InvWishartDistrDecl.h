#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class InvWishartDistrDecl: public swift::predecl::PreDecl {
public:
  InvWishartDistrDecl();
  virtual ~InvWishartDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
