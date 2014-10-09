#include "PreDeclList.h"

namespace swift {
namespace predecl {

// PreDecl Distributions

const BernoulliDistrDecl PreDeclList::bernoulliDistr =
    BernoulliDistrDecl();

const BetaDistrDecl PreDeclList::betaDistr =
    BetaDistrDecl();

const BinomialDistrDecl PreDeclList::binomialDistr =
    BinomialDistrDecl();

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

const MultinomialDistrDecl PreDeclList::multinomialDistr =
    MultinomialDistrDecl();

const UniformChoiceDistrDecl PreDeclList::uniformChoiceDistr =
    UniformChoiceDistrDecl();

const UniformIntDistrDecl PreDeclList::uniformIntDistr =
    UniformIntDistrDecl();

const UniformRealDistrDecl PreDeclList::uniformRealDistr =
    UniformRealDistrDecl();

const UniformVectorDistrDecl PreDeclList::uniformVectorDistr =
    UniformVectorDistrDecl();

// PreDecl Functions
const LoadRealMatrixFuncDecl PreDeclList::loadRealMatrixFuncDecl =
    LoadRealMatrixFuncDecl();
const PrevFuncDecl PreDeclList::prevFuncDecl = 
    PrevFuncDecl();
const ToIntFuncDecl PreDeclList::toIntFuncDecl =
    ToIntFuncDecl();
const ToRealFuncDecl PreDeclList::toRealFuncDecl =
    ToRealFuncDecl();
const ToMatrixFuncDecl PreDeclList::toMatrixFuncDecl =
    ToMatrixFuncDecl();
const ToStringFuncDecl PreDeclList::toStringFuncDecl =
    ToStringFuncDecl();

// Functions using Builtin Function Interface

// general math function: both for real and matrix
const std::vector<std::string> PreDeclList::mathFuncList{ "abs", "exp", "log", "sqrt", "round", "floor", "ceil", "tan", "sin", "cos" };
// matrix initialization functions
const std::vector<std::string> PreDeclList::matConstructFuncList{ "eye", "zeros" };
const MatrixConstructFuncDecl PreDeclList::onesFuncDecl =
    MatrixConstructFuncDecl("ones"); // Should be mannually register in PredeclFunctory
// function from matrix to real
const std::vector<std::string> PreDeclList::matRealFuncList{ "trace", "det", "norm", "cond", "log_det"};
const MatrixRealFuncDecl PreDeclList::asScalarFuncDecl =
    MatrixRealFuncDecl("as_scalar"); // Should be mannually register in PredeclFunctory
// function from matrix to int
const std::vector<std::string> PreDeclList::matIntFuncList{ "numRows", "numCols", "rank" };
// function from matrix to matrix
const std::vector<std::string> PreDeclList::matMatFuncList{ "trans", "chol", "inv", "pinv", "diagmat" };
// matrix stacking functions
const std::vector<std::string> PreDeclList::matStackFuncList{ "vstack", "hstack" };

std::map<std::string, std::shared_ptr<PreDecl>> PreDeclList::initFuncStore() {
  std::map<std::string, std::shared_ptr<PreDecl>> ret;
  for (auto& s : mathFuncList)
    ret[s] = std::make_shared<MathFuncDecl>(s);
  for (auto& s : matConstructFuncList)
    ret[s] = std::make_shared<MatrixConstructFuncDecl>(s);
  for (auto& s : matRealFuncList)
    ret[s] = std::make_shared<MatrixRealFuncDecl>(s);
  for (auto& s : matIntFuncList)
    ret[s] = std::make_shared<MatrixIntFuncDecl>(s);
  for (auto& s : matMatFuncList)
    ret[s] = std::make_shared<MatrixMatrixFuncDecl>(s);
  for (auto& s : matStackFuncList)
    ret[s] = std::make_shared<MatrixStackFuncDecl>(s);

  // Matrix Subset Functions
  ret["getrow"] = std::make_shared<MatrixSubsetFuncDecl>("_mat_getrow", 1);
  ret["getcol"] = std::make_shared<MatrixSubsetFuncDecl>("_mat_getcol", 1);
  ret["getrows"] = std::make_shared<MatrixSubsetFuncDecl>("_mat_getrows", 2);
  ret["getcols"] = std::make_shared<MatrixSubsetFuncDecl>("_mat_getcols", 2);
  ret["submat"] = std::make_shared<MatrixSubsetFuncDecl>("_mat_submat", 4);
  ret["repmat"] = std::make_shared<MatrixSubsetFuncDecl>("repmat", 2);

  // Set Functions
  ret["sum"] = std::make_shared<SetFuncDecl>("_set_sum");
  ret["min"] = std::make_shared<SetFuncDecl>("_set_min");
  ret["max"] = std::make_shared<SetFuncDecl>("_set_max");

  // Special Functions with Different Names
  ret["logdet"] = ret["log_det"];
  ret["transpose"] = ret["trans"];
  ret["diag"] = ret["diagmat"];
  ret["colsum"] = std::make_shared<MatrixMatrixFuncDecl>("_predecl_colsum");
  ret["rowsum"] = std::make_shared<MatrixMatrixFuncDecl>("_predecl_rowsum");
  ret["matsum"] = std::make_shared<MatrixRealFuncDecl>("accu");

  return ret;
}

const std::map<std::string, std::shared_ptr<PreDecl>> PreDeclList::funcStore = PreDeclList::initFuncStore();

PreDeclList::PreDeclList() {
}

PreDeclList::~PreDeclList() {
}

}
}
