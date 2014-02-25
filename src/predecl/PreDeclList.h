#pragma once

// PreDecl Distributions
#include "BernoulliDistrDecl.h"
#include "BetaDistrDecl.h"
#include "BooleanDistrDecl.h"
#include "CategoricalDistrDecl.h"
#include "GammaDistrDecl.h"
#include "GaussianDistrDecl.h"
#include "PoissonDistrDecl.h"
#include "UniformChoiceDistrDecl.h"
// PreDecl Functions
#include "PrevFuncDecl.h"

namespace swift {
namespace predecl {

class PreDeclList {
public:
  PreDeclList();
  ~PreDeclList();

  // PreDecl Distrbutions
  static const BernoulliDistrDecl bernoulliDistr;
  static const BetaDistrDecl betaDistr;
  static const BooleanDistrDecl booleanDistr;
  static const CategoricalDistrDecl categoricalDistr;
  static const GammaDistrDecl gammaDistr;
  static const GaussianDistrDecl gaussianDistr;
  static const PoissonDistrDecl poissonDistr;
  static const UniformChoiceDistrDecl uniformChoiceDistr;
  // PreDecl Functions
  static const PrevFuncDecl prevFuncDecl;
};

}
}
