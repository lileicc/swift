#include "PreDeclDistrList.h"

namespace swift { namespace predecl {

const CategoricalDistrDecl PreDeclDistrList::categoricalDistr = CategoricalDistrDecl();

const PoissonDistrDecl PreDeclDistrList::poissonDistr = PoissonDistrDecl();

PreDeclDistrList::PreDeclDistrList() {
}

PreDeclDistrList::~PreDeclDistrList() {
}

}
}