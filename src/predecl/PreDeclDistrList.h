#pragma once

#include "BernoulliDistrDecl.h"
#include "BooleanDistrDecl.h"
#include "CategoricalDistrDecl.h"
#include "GaussianDistrDecl.h"
#include "PoissonDistrDecl.h"
#include "UniformChoiceDistrDecl.h"

namespace swift {
namespace predecl {

class PreDeclDistrList {
public:
  PreDeclDistrList();
  ~PreDeclDistrList();

  static const BernoulliDistrDecl bernoulliDistr;
  static const BooleanDistrDecl booleanDistr;
  static const CategoricalDistrDecl categoricalDistr;
  static const GaussianDistrDecl gaussianDistr;
  static const PoissonDistrDecl poissonDistr;
  static const UniformChoiceDistrDecl uniformChoiceDistr;
};

}
}
