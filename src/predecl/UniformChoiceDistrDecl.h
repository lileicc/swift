#pragma once
#include "PreDeclDistr.h"

namespace swift {
namespace predecl {

class UniformChoiceDistrDecl: public swift::predecl::PreDeclDistr {
public:
  UniformChoiceDistrDecl();
  virtual ~UniformChoiceDistrDecl();

  virtual std::shared_ptr<ir::Distribution>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
