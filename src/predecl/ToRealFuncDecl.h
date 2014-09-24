#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class ToRealFuncDecl: public swift::predecl::PreDecl {
public:
  ToRealFuncDecl();
  virtual ~ToRealFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
