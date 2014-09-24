#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class LoadRealMatrixFuncDecl: public swift::predecl::PreDecl {
public:
  LoadRealMatrixFuncDecl();
  virtual ~LoadRealMatrixFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
