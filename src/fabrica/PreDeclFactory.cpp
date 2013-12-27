#include "PreDeclFactory.h"

#include "../predecl/PreDeclDistrList.h"

namespace swift { namespace fabrica {

PreDeclFactory::PreDeclFactory() {
  distr[predecl::PreDeclDistrList::categoricalDistr.getName()]
    = &predecl::PreDeclDistrList::categoricalDistr;
  distr[predecl::PreDeclDistrList::poissonDistr.getName()]
    = &predecl::PreDeclDistrList::poissonDistr;
}


PreDeclFactory::~PreDeclFactory() {
}

const predecl::PreDeclDistr* PreDeclFactory::getDistr(std::string name) {
  if (distr.count(name) == 0) return NULL;
  return distr[name];
}

}
}