#include "PoissonDistrDecl.h"

namespace swift { namespace predecl {
PoissonDistrDecl::PoissonDistrDecl()
  :PreDeclDistr(std::string("Poisson")){
}

PoissonDistrDecl::~PoissonDistrDecl() {
}

std::shared_ptr<ir::Distribution> PoissonDistrDecl::getNew
  (std::vector<std::shared_ptr<ir::Expr>>& args, fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr || args[0]->getTyp() != fact->getTy(ir::IRConstString::DOUBLE))
    return nullptr;
  // TODO: ONLY accept double literal??
  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setTyp(fact->getTy(ir::IRConstString::INT));
  return ret;
}

}
}
