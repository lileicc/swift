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
  decls[predecl::PreDeclList::binomialDistr.getName()] =
    &predecl::PreDeclList::binomialDistr;
  decls[predecl::PreDeclList::booleanDistr.getName()] =
    &predecl::PreDeclList::booleanDistr;
  decls[predecl::PreDeclList::categoricalDistr.getName()] =
    &predecl::PreDeclList::categoricalDistr;
  decls[predecl::PreDeclList::dirichletDistr.getName()] =
    &predecl::PreDeclList::dirichletDistr;
  decls[predecl::PreDeclList::discreteDistr.getName()] =
    &predecl::PreDeclList::discreteDistr;
  decls[predecl::PreDeclList::exponentialDistr.getName()] =
    &predecl::PreDeclList::exponentialDistr;
  decls[predecl::PreDeclList::gammaDistr.getName()] =
    &predecl::PreDeclList::gammaDistr;
  decls[predecl::PreDeclList::gaussianDistr.getName()] =
    &predecl::PreDeclList::gaussianDistr;
  decls[predecl::PreDeclList::geometricDistr.getName()] =
    &predecl::PreDeclList::geometricDistr;
  decls[predecl::PreDeclList::diaggaussianDistr.getName()] =
    &predecl::PreDeclList::diaggaussianDistr;
  decls[predecl::PreDeclList::invWishartDistr.getName()] =
    &predecl::PreDeclList::invWishartDistr;
  decls[predecl::PreDeclList::multivargaussianDistr.getName()] =
    &predecl::PreDeclList::multivargaussianDistr;
  decls[predecl::PreDeclList::multinomialDistr.getName()] =
    &predecl::PreDeclList::multinomialDistr;
  decls[predecl::PreDeclList::poissonDistr.getName()] =
      &predecl::PreDeclList::poissonDistr;
  decls[predecl::PreDeclList::precisiongaussianDistr.getName()] =
      &predecl::PreDeclList::precisiongaussianDistr;
  decls[predecl::PreDeclList::truncatedGaussDistr.getName()] =
    &predecl::PreDeclList::truncatedGaussDistr;
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
  decls[predecl::PreDeclList::toMatrixFuncDecl.getName()] =
    &predecl::PreDeclList::toMatrixFuncDecl;
  decls[predecl::PreDeclList::toStringFuncDecl.getName()] =
    &predecl::PreDeclList::toStringFuncDecl;

  // Special Commonly used Predecl Functions
  decls[predecl::PreDeclList::onesFuncDecl.getName()] =
    &predecl::PreDeclList::onesFuncDecl;
  decls[predecl::PreDeclList::asScalarFuncDecl.getName()] =
    &predecl::PreDeclList::asScalarFuncDecl;

  // Different Names Referring to the Same Function/Distribution
  decls["toString"] = &predecl::PreDeclList::toStringFuncDecl;
  decls["UnivarGaussian"] = &predecl::PreDeclList::gaussianDistr;
  decls["toMatrix"] = &predecl::PreDeclList::toMatrixFuncDecl;

  // Add Builtin Function using Function Interface
  for (auto& s : predecl::PreDeclList::funcStore)
    decls[s.first] = s.second.get();
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
