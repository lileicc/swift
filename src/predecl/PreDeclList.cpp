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


// PreDecl Functions

const PrevFuncDecl PreDeclList::prevFuncDecl = 
    PrevFuncDecl();

// Functions using Builtin Function Interface

// general math function: both for real and matrix
const std::vector<std::string> mathFuncList{"abs","exp","log","sqrt","round","floor","ceil","tan","sin","cos"};
// function from matrix to real
const std::vector<std::string> matRealFuncList{ "trace", "det", "norm", "cond", "as_scalar" };
// function from matrix to matrix
const std::vector<std::string> matMatFuncList{ "trans", "transpose", "chol", "inv", "pinv"};

PreDeclList::PreDeclList() {
  for (auto& s: mathFuncList) 
    funcStore[s] = new MathFuncDecl(s);
  for (auto& s : matRealFuncList)
    funcStore[s] = new MatrixRealFuncDecl(s);
  for (auto& s : matMatFuncList)
    funcStore[s] = new MatrixMatrixFuncDecl(s);
}

PreDeclList::~PreDeclList() {
  for (auto& s: funcStore)
    delete s.second;
}

}
}
