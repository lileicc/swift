#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class TruncatedGaussDistrDecl: public swift::predecl::PreDecl {
public:
  TruncatedGaussDistrDecl();
  virtual ~TruncatedGaussDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
