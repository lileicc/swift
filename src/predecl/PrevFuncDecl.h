#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class PrevFuncDecl: public swift::predecl::PreDecl {
public:
  PrevFuncDecl();
  virtual ~PrevFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
