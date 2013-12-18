#pragma once
#include "PreDeclDistr.h"

namespace swift { namespace predecl {

class CategoricalDistrDecl :
  public swift::predecl::PreDeclDistr {
public:
  CategoricalDistrDecl();
  virtual ~CategoricalDistrDecl();
};

}
}