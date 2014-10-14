#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class SetAggrFuncDecl: public swift::predecl::PreDecl {
public:
  SetAggrFuncDecl(std::string name);
  virtual ~SetAggrFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
