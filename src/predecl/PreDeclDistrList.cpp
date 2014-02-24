#include "PreDeclDistrList.h"

namespace swift {
namespace predecl {

const BernoulliDistrDecl PreDeclDistrList::bernoulliDistr =
    BernoulliDistrDecl();

const BooleanDistrDecl PreDeclDistrList::booleanDistr =
    BooleanDistrDecl();

const CategoricalDistrDecl PreDeclDistrList::categoricalDistr =
    CategoricalDistrDecl();

const PoissonDistrDecl PreDeclDistrList::poissonDistr = PoissonDistrDecl();

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
