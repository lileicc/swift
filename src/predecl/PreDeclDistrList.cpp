#include "PreDeclDistrList.h"

namespace swift {
namespace predecl {

const BernoulliDistrDecl PreDeclDistrList::bernoulliDistr =
    BernoulliDistrDecl();

const BetaDistrDecl PreDeclDistrList::betaDistr =
    BetaDistrDecl();

const BooleanDistrDecl PreDeclDistrList::booleanDistr =
    BooleanDistrDecl();

const CategoricalDistrDecl PreDeclDistrList::categoricalDistr =
    CategoricalDistrDecl();

const PoissonDistrDecl PreDeclDistrList::poissonDistr = PoissonDistrDecl();

const GammaDistrDecl PreDeclDistrList::gammaDistr =
    GammaDistrDecl();

const GaussianDistrDecl PreDeclDistrList::gaussianDistr =
    GaussianDistrDecl();

const UniformChoiceDistrDecl PreDeclDistrList::uniformChoiceDistr =
    UniformChoiceDistrDecl();

PreDeclDistrList::PreDeclDistrList() {
}

PreDeclDistrList::~PreDeclDistrList() {
}

}
}
