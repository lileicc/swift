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
#include "UniformVectorDistrDecl.h"
// PreDecl Functions
#include "PrevFuncDecl.h"
// BuiltinFunction Interface
#include "MathFuncDecl.h"
#include "MatrixMatrixFuncDecl.h"
#include "MatrixRealFuncDecl.h"
#include "MatrixInitFuncDecl.h"

#include <vector>
#include <string>
#include <map>
#include <memory>

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
  static const UniformVectorDistrDecl uniformVectorDistr;
  // PreDecl Functions
  static const PrevFuncDecl prevFuncDecl;
  
  // Functions using Builtin Function Interface
  static const std::map<std::string, std::shared_ptr<PreDecl>> funcStore; // used to store builtin functions using function interface
  static const std::vector<std::string> mathFuncList;
  static const std::vector<std::string> matRealFuncList;
  static const std::vector<std::string> matMatFuncList;
  static const std::vector<std::string> matInitFuncList;

private:
  static std::map<std::string, std::shared_ptr<PreDecl>> initFuncStore();
};

}
}
