#pragma once

#include "BernoulliDistrDecl.h"
#include "BetaDistrDecl.h"
#include "BooleanDistrDecl.h"
#include "CategoricalDistrDecl.h"
#include "GammaDistrDecl.h"
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
  static const BetaDistrDecl betaDistr;
  static const BooleanDistrDecl booleanDistr;
  static const CategoricalDistrDecl categoricalDistr;
  static const GammaDistrDecl gammaDistr;
  static const GaussianDistrDecl gaussianDistr;
  static const PoissonDistrDecl poissonDistr;
  static const UniformChoiceDistrDecl uniformChoiceDistr;
};

}
}
