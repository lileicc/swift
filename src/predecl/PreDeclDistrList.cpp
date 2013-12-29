#include "PreDeclDistrList.h"

namespace swift { namespace predecl {

const CategoricalDistrDecl PreDeclDistrList::categoricalDistr = CategoricalDistrDecl();

const PoissonDistrDecl PreDeclDistrList::poissonDistr = PoissonDistrDecl();

const UniformChoiceDistrDecl PreDeclDistrList::uniformChoiceDistr = UniformChoiceDistrDecl();

PreDeclDistrList::PreDeclDistrList() {
}

PreDeclDistrList::~PreDeclDistrList() {
}

}
}