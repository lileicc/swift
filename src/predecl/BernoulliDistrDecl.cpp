#include "BernoulliDistrDecl.h"

#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
BernoulliDistrDecl::BernoulliDistrDecl() :
    PreDecl(std::string("Bernoulli")) {
}

BernoulliDistrDecl::~BernoulliDistrDecl() {
}

std::shared_ptr<ir::Expr> BernoulliDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  // Note: We only accept double
  if (args[0]->getTyp() != fact->getTy(ir::IRConstString::DOUBLE))
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
