#include "UniformIntDistrDecl.h"

namespace swift {
namespace predecl {
UniformIntDistrDecl::UniformIntDistrDecl() :
    PreDecl(std::string("UniformInt")) {
}

UniformIntDistrDecl::~UniformIntDistrDecl() {
}

std::shared_ptr<ir::Expr> UniformIntDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2 || args[0] == nullptr || args[1] == nullptr)
    return nullptr;

  auto int_ty = fact->getTy(ir::IRConstString::INT);
  // Note: We both accept NON-NEGATIVE integer and double
  if (args[0]->getTyp() != int_ty || args[1]->getTyp() != int_ty)
    return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(int_ty);
  ret->processArgRandomness();
  ret->setRandom(true);
  return ret;
}

}
}
