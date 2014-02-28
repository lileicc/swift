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

const UniformChoiceDistrDecl PreDeclList::uniformChoiceDistr =
    UniformChoiceDistrDecl();


// PreDecl Functions

const PrevFuncDecl PreDeclList::prevFuncDecl = 
    PrevFuncDecl();


PreDeclList::PreDeclList() {
}

PreDeclList::~PreDeclList() {
}

}
}
