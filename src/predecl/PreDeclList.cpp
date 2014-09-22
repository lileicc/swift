#include "PreDeclList.h"

namespace swift {
namespace predecl {

// PreDecl Distributions

const BernoulliDistrDecl PreDeclList::bernoulliDistr =
    BernoulliDistrDecl();

const BetaDistrDecl PreDeclList::betaDistr =
    BetaDistrDecl();

const BooleanDistrDecl PreDeclList::booleanDistr =
    BooleanDistrDecl();

const CategoricalDistrDecl PreDeclList::categoricalDistr =
    CategoricalDistrDecl();

const DirichletDistrDecl PreDeclList::dirichletDistr =
    DirichletDistrDecl();

const DiscreteDistrDecl PreDeclList::discreteDistr = 
    DiscreteDistrDecl();

const PoissonDistrDecl PreDeclList::poissonDistr = PoissonDistrDecl();

const GammaDistrDecl PreDeclList::gammaDistr =
    GammaDistrDecl();

const GaussianDistrDecl PreDeclList::gaussianDistr =
    GaussianDistrDecl();

const MultivarGaussianDistrDecl PreDeclList::multivargaussianDistr =
    MultivarGaussianDistrDecl();

const UniformChoiceDistrDecl PreDeclList::uniformChoiceDistr =
    UniformChoiceDistrDecl();

const UniformVectorDistrDecl PreDeclList::uniformVectorDistr =
    UniformVectorDistrDecl();

// PreDecl Functions

const PrevFuncDecl PreDeclList::prevFuncDecl = 
    PrevFuncDecl();

// Functions using Builtin Function Interface

// general math function: both for real and matrix
const std::vector<std::string> PreDeclList::mathFuncList{ "abs", "exp", "log", "sqrt", "round", "floor", "ceil", "tan", "sin", "cos" };
// function from matrix to real
const std::vector<std::string> PreDeclList::matRealFuncList{ "trace", "det", "norm", "cond", "as_scalar" };
// function from matrix to matrix
const std::vector<std::string> PreDeclList::matMatFuncList{ "trans", "transpose", "chol", "inv", "pinv", "sum", "diag" };
// matrix initialization functions
const std::vector<std::string> PreDeclList::matInitFuncList{ "eye", "zeros", "ones" };

std::map<std::string, std::shared_ptr<PreDecl>> PreDeclList::initFuncStore() {
  std::map<std::string, std::shared_ptr<PreDecl>> ret;
  for (auto& s : mathFuncList)
    ret[s] = std::make_shared<MathFuncDecl>(s);
  for (auto& s : matRealFuncList)
    ret[s] = std::make_shared<MatrixRealFuncDecl>(s);
  for (auto& s : matMatFuncList)
    ret[s] = std::make_shared<MatrixMatrixFuncDecl>(s);
  for (auto& s : matInitFuncList)
    ret[s] = std::make_shared<MatrixInitFuncDecl>(s);
  return ret;
}

const std::map<std::string, std::shared_ptr<PreDecl>> PreDeclList::funcStore = PreDeclList::initFuncStore();

PreDeclList::PreDeclList() {
}

PreDeclList::~PreDeclList() {
}

}
}
