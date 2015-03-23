#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class ToMatrixFuncDecl: public swift::predecl::PreDecl {
public:
  ToMatrixFuncDecl();
  virtual ~ToMatrixFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
