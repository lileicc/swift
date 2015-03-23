#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class BinomialDistrDecl: public swift::predecl::PreDecl {
public:
  BinomialDistrDecl();
  virtual ~BinomialDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
