#include "PoissonDistrDecl.h"

#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
PoissonDistrDecl::PoissonDistrDecl() :
    PreDecl(std::string("Poisson")) {
}

PoissonDistrDecl::~PoissonDistrDecl() {
}

std::shared_ptr<ir::Expr> PoissonDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  // Note: We both accept NON-NEGATIVE integer and double
  if (args[0]->getTyp() != fact->getTy(ir::IRConstString::DOUBLE)
      && args[0]->getTyp() != fact->getTy(ir::IRConstString::INT))
    return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::INT));
  return ret;
}

}
}
