#pragma once

#include "CategoricalDistrDecl.h"
#include "PoissonDistrDecl.h"
#include "UniformChoiceDistrDecl.h"

namespace swift {
namespace predecl {

class PreDeclDistrList {
public:
  PreDeclDistrList();
  ~PreDeclDistrList();

  static const CategoricalDistrDecl categoricalDistr;
  static const PoissonDistrDecl poissonDistr;
  static const UniformChoiceDistrDecl uniformChoiceDistr;
};

}
}
