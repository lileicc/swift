#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class SetFuncDecl: public swift::predecl::PreDecl {
public:
  SetFuncDecl(std::string name);
  virtual ~SetFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
