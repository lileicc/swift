#include "PrecisionGaussianDistrDecl.h"

namespace swift {
namespace predecl {
PrecisionGaussianDistrDecl::PrecisionGaussianDistrDecl() :
    PreDecl(std::string("PrecisionGaussian")) {
}

PrecisionGaussianDistrDecl::~PrecisionGaussianDistrDecl() {
}

std::shared_ptr<ir::Expr> PrecisionGaussianDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2 || args[0] == nullptr || args[1] == nullptr)
    return nullptr;

  // Note: We only accept matrix as arguments
  if (args[0]->getTyp() != fact->getTy(ir::IRConstString::MATRIX))
    return nullptr;
  if ((args[1]->getTyp() != fact->getTy(ir::IRConstString::MATRIX)))
    return nullptr;

  std::string name = this->getName();

  auto ret = std::make_shared<ir::Distribution>(name, this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::MATRIX));
  ret->processArgRandomness();
  ret->setRandom(true);
  return ret;
}

}
}
