#pragma once
#include "PreDeclDistr.h"

namespace swift { namespace predecl {

class CategoricalDistrDecl :
  public swift::predecl::PreDeclDistr {
public:
  CategoricalDistrDecl();
  virtual ~CategoricalDistrDecl();

  virtual std::shared_ptr<ir::Distribution>
    getNew(std::vector<std::shared_ptr<ir::Expr>>& args, fabrica::TypeFactory* fact) const ;
};

}
}