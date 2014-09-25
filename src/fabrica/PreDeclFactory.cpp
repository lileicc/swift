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
  decls[predecl::PreDeclList::uniformIntDistr.getName()] =
    &predecl::PreDeclList::uniformIntDistr;
  decls[predecl::PreDeclList::uniformRealDistr.getName()] =
    &predecl::PreDeclList::uniformRealDistr;
  decls[predecl::PreDeclList::uniformChoiceDistr.getName()] =
      &predecl::PreDeclList::uniformChoiceDistr;
  decls[predecl::PreDeclList::uniformVectorDistr.getName()] =
    &predecl::PreDeclList::uniformVectorDistr;

  // Predecl Functions
  decls[predecl::PreDeclList::loadRealMatrixFuncDecl.getName()] =
    &predecl::PreDeclList::loadRealMatrixFuncDecl;
  decls[predecl::PreDeclList::prevFuncDecl.getName()] =
    &predecl::PreDeclList::prevFuncDecl;
  decls[predecl::PreDeclList::toIntFuncDecl.getName()] =
    &predecl::PreDeclList::toIntFuncDecl;
  decls[predecl::PreDeclList::toRealFuncDecl.getName()] =
    &predecl::PreDeclList::toRealFuncDecl;

  // Add Builtin Function using Function Interface
  for (auto& s : predecl::PreDeclList::funcStore)
    decls[s.first] = s.second.get();
  // Special Matrix Builtin Function
  decls[predecl::PreDeclList::asScalarFuncDecl.getName()] =
    &predecl::PreDeclList::asScalarFuncDecl;
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
