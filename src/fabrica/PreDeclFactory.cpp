#include "PreDeclFactory.h"

#include "../predecl/PreDeclDistrList.h"

namespace swift { namespace fabrica {

PreDeclFactory::PreDeclFactory() {
  distr[predecl::PreDeclDistrList::categoricalDistr.getName()][""]
    = &predecl::PreDeclDistrList::categoricalDistr;
}


PreDeclFactory::~PreDeclFactory() {
}

}
}