#include "InvWishartDistrDecl.h"

namespace swift {
namespace predecl {

InvWishartDistrDecl::InvWishartDistrDecl() :
  PreDecl(std::string("InvWishart")) {
}

InvWishartDistrDecl::~InvWishartDistrDecl() {
}

std::shared_ptr<ir::Expr> InvWishartDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2 || args[0] == nullptr || args[1] == nullptr)
    return nullptr;

  // First arg: matrix, second arg: Non-negative Integer
  if (args[0]->getTyp() != fact->getTy(ir::IRConstString::MATRIX))
    return nullptr;
  if (args[1]->getTyp() != fact->getTy(ir::IRConstString::INT))
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
