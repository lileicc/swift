#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class ToStringFuncDecl: public swift::predecl::PreDecl {
public:
  ToStringFuncDecl();
  virtual ~ToStringFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
