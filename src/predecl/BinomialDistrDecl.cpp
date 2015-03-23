#include "BinomialDistrDecl.h"

namespace swift {
namespace predecl {
BinomialDistrDecl::BinomialDistrDecl() :
    PreDecl(std::string("Binomial")) {
}

BinomialDistrDecl::~BinomialDistrDecl() {
}

std::shared_ptr<ir::Expr> BinomialDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2 || args[0] == nullptr || args[1] == nullptr)
    return nullptr;

  // Note: We only accept NON-NEGATIVE integer and double in [0,1]
  if (args[0]->getTyp() != fact->getTy(ir::IRConstString::INT)
    || args[1]->getTyp() != fact->getTy(ir::IRConstString::DOUBLE))
    return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::INT));
  ret->processArgRandomness();
  ret->setRandom(true);
  return ret;
}

}
}
