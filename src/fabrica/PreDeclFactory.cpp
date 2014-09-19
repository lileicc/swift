#include "PreDeclFactory.h"

#include "../predecl/PreDeclList.h"

namespace swift {
namespace fabrica {

PreDeclFactory::PreDeclFactory() {
  // Predeclared Distributions
  decls[predecl::PreDeclList::bernoulliDistr.getName()] =
    &predecl::PreDeclList::bernoulliDistr;
  decls[predecl::PreDeclList::betaDistr.getName()] =
    &predecl::PreDeclList::betaDistr;
  decls[predecl::PreDeclList::booleanDistr.getName()] =
    &predecl::PreDeclList::booleanDistr;
  decls[predecl::PreDeclList::categoricalDistr.getName()] =
    &predecl::PreDeclList::categoricalDistr;
  decls[predecl::PreDeclList::dirichletDistr.getName()] =
    &predecl::PreDeclList::dirichletDistr;
  decls[predecl::PreDeclList::discreteDistr.getName()] =
    &predecl::PreDeclList::discreteDistr;
  decls[predecl::PreDeclList::gammaDistr.getName()] =
    &predecl::PreDeclList::gammaDistr;
  decls[predecl::PreDeclList::gaussianDistr.getName()] =
    &predecl::PreDeclList::gaussianDistr;
  decls[predecl::PreDeclList::multivargaussianDistr.getName()] =
    &predecl::PreDeclList::multivargaussianDistr;
  decls[predecl::PreDeclList::poissonDistr.getName()] =
      &predecl::PreDeclList::poissonDistr;
  decls[predecl::PreDeclList::uniformChoiceDistr.getName()] =
      &predecl::PreDeclList::uniformChoiceDistr;
  
  // Predecl Functions
  decls[predecl::PreDeclList::prevFuncDecl.getName()] =
    &predecl::PreDeclList::prevFuncDecl;

  // Add Builtin Function using Function Interface
  decls.insert(predecl::PreDeclList::funcStore.begin(), predecl::PreDeclList::funcStore.end());
}

PreDeclFactory::~PreDeclFactory() {
}

const predecl::PreDecl* PreDeclFactory::getDecl(std::string name) {
  if (decls.count(name) == 0)
    return NULL;
  return decls[name];
}

}
}
