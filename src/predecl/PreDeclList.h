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
#include "UniformIntDistrDecl.h"
#include "UniformRealDistrDecl.h"
#include "UniformVectorDistrDecl.h"
// PreDecl Functions
#include "LoadRealMatrixFuncDecl.h"
#include "PrevFuncDecl.h"
#include "ToIntFuncDecl.h"
#include "ToRealFuncDecl.h"
// BuiltinFunction Interface
#include "MathFuncDecl.h"
#include "MatrixMatrixFuncDecl.h"
#include "MatrixRealFuncDecl.h"
#include "MatrixInitFuncDecl.h"
#include "MatrixStackFuncDecl.h"
#include "MatrixSubsetFuncDecl.h"
#include "SetFuncDecl.h"

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
  static const UniformIntDistrDecl uniformIntDistr;
  static const UniformRealDistrDecl uniformRealDistr;
  static const UniformVectorDistrDecl uniformVectorDistr;
  // PreDecl Functions
  static const LoadRealMatrixFuncDecl loadRealMatrixFuncDecl;
  static const PrevFuncDecl prevFuncDecl;
  static const ToIntFuncDecl toIntFuncDecl;
  static const ToRealFuncDecl toRealFuncDecl;
  
  // Functions using Builtin Function Interface
  static const std::map<std::string, std::shared_ptr<PreDecl>> funcStore; // used to store builtin functions using function interface
  static const std::vector<std::string> mathFuncList;
  static const std::vector<std::string> matRealFuncList;
  static const std::vector<std::string> matMatFuncList;
  static const std::vector<std::string> matInitFuncList;
  static const std::vector<std::string> matStackFuncList;
  static const MatrixRealFuncDecl asScalarFuncDecl; // Special Usage of as_scalar

private:
  static std::map<std::string, std::shared_ptr<PreDecl>> initFuncStore();
};

}
}
