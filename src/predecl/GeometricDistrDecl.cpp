#include "GeometricDistrDecl.h"

#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
GeometricDistrDecl::GeometricDistrDecl() :
    PreDecl(std::string("Geometric")) {
}

GeometricDistrDecl::~GeometricDistrDecl() {
}

std::shared_ptr<ir::Expr> GeometricDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  // Note: We both accept NON-NEGATIVE integer and double
  for(int i = 0; i < 1; ++ i)
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
