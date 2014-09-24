#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class ToIntFuncDecl: public swift::predecl::PreDecl {
public:
  ToIntFuncDecl();
  virtual ~ToIntFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
