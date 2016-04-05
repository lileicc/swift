#include "DiagGaussianDistrDecl.h"

#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
DiagGaussianDistrDecl::DiagGaussianDistrDecl() :
    PreDecl(std::string("DiagGaussian")) {
}

DiagGaussianDistrDecl::~DiagGaussianDistrDecl() {
}

std::shared_ptr<ir::Expr> DiagGaussianDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2 || args[0] == nullptr || args[1] == nullptr)
    return nullptr;

  // Note: We only accept matrix as arguments
  if (args[0]->getTyp() != fact->getTy(ir::IRConstString::MATRIX))
    return nullptr;
  // Note: We only accept matrix as arguments
  if (args[1]->getTyp() != fact->getTy(ir::IRConstString::MATRIX))
    return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::MATRIX));
  ret->processArgRandomness();
  ret->setRandom(true);
  return ret;
}

}
}
