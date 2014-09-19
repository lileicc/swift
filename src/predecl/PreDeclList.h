#pragma once

// PreDecl Distributions
#include "BernoulliDistrDecl.h"
#include "BetaDistrDecl.h"
#include "BooleanDistrDecl.h"
#include "CategoricalDistrDecl.h"
#include "DirichletDistrDecl.h"
#include "DiscreteDistrDecl.h"
#include "GammaDistrDecl.h"
#include "GaussianDistrDecl.h"
#include "MultivarGaussianDistrDecl.h"
#include "PoissonDistrDecl.h"
#include "UniformChoiceDistrDecl.h"
// PreDecl Functions
#include "PrevFuncDecl.h"
// BuiltinFunction Interface
#include "MathFuncDecl.h"
#include "MatrixMatrixFuncDecl.h"
#include "MatrixRealFuncDecl.h"

#include <vector>
#include <string>
#include <map>

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
  static const DirichletDistrDecl dirichletDistr;
  static const DiscreteDistrDecl discreteDistr;
  static const GammaDistrDecl gammaDistr;
  static const GaussianDistrDecl gaussianDistr;
  static const MultivarGaussianDistrDecl multivargaussianDistr;
  static const PoissonDistrDecl poissonDistr;
  static const UniformChoiceDistrDecl uniformChoiceDistr;
  // PreDecl Functions
  static const PrevFuncDecl prevFuncDecl;
  
  // Functions using Builtin Function Interface
  static std::map<std::string, PreDecl*> funcStore; // used to store builtin functions using function interface
  static const std::vector<std::string> mathFuncList;
  static const std::vector<std::string> matRealFuncList;
  static const std::vector<std::string> matMatFuncList;
};

}
}
