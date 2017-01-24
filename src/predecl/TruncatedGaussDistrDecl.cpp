#include "TruncatedGaussDistrDecl.h"

#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
TruncatedGaussDistrDecl::TruncatedGaussDistrDecl() :
    PreDecl(std::string("TruncatedGauss")) {
}

TruncatedGaussDistrDecl::~TruncatedGaussDistrDecl() {
}

std::shared_ptr<ir::Expr> TruncatedGaussDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 4
      || args[0] == nullptr || args[1] == nullptr
      || args[2] == nullptr || args[3] == nullptr)
    return nullptr;

  // Note: We both accept integer and double (second term must be positive)
  for(int i = 0; i < 4; ++ i)
    if ((args[i]->getTyp() != fact->getTy(ir::IRConstString::DOUBLE)
       && args[i]->getTyp() != fact->getTy(ir::IRConstString::INT)))
      return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::DOUBLE));
  ret->processArgRandomness();
  ret->setRandom(true);
  return ret;
}

}
}
