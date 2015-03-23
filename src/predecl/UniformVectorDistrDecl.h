#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class UniformVectorDistrDecl: public swift::predecl::PreDecl {
public:
  UniformVectorDistrDecl();
  virtual ~UniformVectorDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
