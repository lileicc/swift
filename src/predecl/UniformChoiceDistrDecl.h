#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class UniformChoiceDistrDecl: public swift::predecl::PreDecl {
public:
  UniformChoiceDistrDecl();
  virtual ~UniformChoiceDistrDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
