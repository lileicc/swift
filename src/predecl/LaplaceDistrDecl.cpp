#include "LaplaceDistrDecl.h"

#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
LaplaceDistrDecl::LaplaceDistrDecl() :
    PreDecl(std::string("Laplace")) {
}

LaplaceDistrDecl::~LaplaceDistrDecl() {
}

std::shared_ptr<ir::Expr> LaplaceDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2 || args[0] == nullptr || args[1] == nullptr)
    return nullptr;

  // Note: We both accept NON-NEGATIVE integer and double
  for(int i = 0; i < 2; ++ i)
    if ((args[i]->getTyp() != fact->getTy(ir::IRConstString::DOUBLE)
       && args[i]->getTyp() != fact->getTy(ir::IRConstString::INT)))
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
