#pragma once

// PreDecl Distributions
#include "BernoulliDistrDecl.h"
#include "BetaDistrDecl.h"
#include "BinomialDistrDecl.h"
#include "BooleanDistrDecl.h"
#include "CategoricalDistrDecl.h"
#include "DiagGaussianDistrDecl.h"
#include "DirichletDistrDecl.h"
#include "DiscreteDistrDecl.h"
#include "ExponentialDistrDecl.h"
#include "GammaDistrDecl.h"
#include "GaussianDistrDecl.h"
#include "GeometricDistrDecl.h"
#include "InvGammaDistrDecl.h"
#include "InvWishartDistrDecl.h"
#include "MultivarGaussianDistrDecl.h"
#include "MultinomialDistrDecl.h"
#include "PoissonDistrDecl.h"
#include "PrecisionGaussianDistrDecl.h"
#include "TruncatedGaussDistrDecl.h"
#include "UniformChoiceDistrDecl.h"
#include "UniformIntDistrDecl.h"
#include "UniformRealDistrDecl.h"
#include "UniformVectorDistrDecl.h"
// PreDecl Functions
#include "LoadRealMatrixFuncDecl.h"
#include "PrevFuncDecl.h"
#include "ToIntFuncDecl.h"
#include "ToRealFuncDecl.h"
#include "ToMatrixFuncDecl.h"
#include "ToStringFuncDecl.h"
// BuiltinFunction Interface
#include "MathFuncDecl.h"
#include "MatrixConstructFuncDecl.h"
#include "MatrixMatrixFuncDecl.h"
#include "MatrixRealFuncDecl.h"
#include "MatrixIntFuncDecl.h"
#include "MatrixStackFuncDecl.h"
#include "MatrixSubsetFuncDecl.h"
#include "SetAggrFuncDecl.h"

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
  static const BinomialDistrDecl binomialDistr;
  static const BooleanDistrDecl booleanDistr;
  static const CategoricalDistrDecl categoricalDistr;
  static const DiagGaussianDistrDecl diaggaussianDistr;
  static const DirichletDistrDecl dirichletDistr;
  static const DiscreteDistrDecl discreteDistr;
  static const ExponentialDistrDecl exponentialDistr;
  static const GammaDistrDecl gammaDistr;
  static const GaussianDistrDecl gaussianDistr;
  static const GeometricDistrDecl geometricDistr;
  static const InvGammaDistrDecl invGammaDistr;
  static const InvWishartDistrDecl invWishartDistr;
  static const MultivarGaussianDistrDecl multivargaussianDistr;
  static const MultinomialDistrDecl multinomialDistr;
  static const PoissonDistrDecl poissonDistr;
  static const PrecisionGaussianDistrDecl precisiongaussianDistr;
  static const TruncatedGaussDistrDecl truncatedGaussDistr;
  static const UniformChoiceDistrDecl uniformChoiceDistr;
  static const UniformIntDistrDecl uniformIntDistr;
  static const UniformRealDistrDecl uniformRealDistr;
  static const UniformVectorDistrDecl uniformVectorDistr;
  // PreDecl Functions
  static const LoadRealMatrixFuncDecl loadRealMatrixFuncDecl;
  static const PrevFuncDecl prevFuncDecl;
  static const ToIntFuncDecl toIntFuncDecl;
  static const ToRealFuncDecl toRealFuncDecl;
  static const ToMatrixFuncDecl toMatrixFuncDecl;
  static const ToStringFuncDecl toStringFuncDecl;

  // Functions using Builtin Function Interface
  static const std::map<std::string, std::shared_ptr<PreDecl>> funcStore; // used to store builtin functions using function interface
  static const std::vector<std::string> mathFuncList;
  static const std::vector<std::string> matConstructFuncList;
  static const std::vector<std::string> matRealFuncList;
  static const std::vector<std::string> matIntFuncList;
  static const std::vector<std::string> matMatFuncList;
  static const std::vector<std::string> matStackFuncList;
  static const MatrixRealFuncDecl asScalarFuncDecl; // Special Usage of as_scalar
  static const MatrixConstructFuncDecl onesFuncDecl; // Special Usage of as_scalar

private:
  static std::map<std::string, std::shared_ptr<PreDecl>> initFuncStore();
};

}
}
