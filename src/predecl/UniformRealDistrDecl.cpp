#include "UniformRealDistrDecl.h"

namespace swift {
namespace predecl {
UniformRealDistrDecl::UniformRealDistrDecl() :
    PreDecl(std::string("UniformReal")) {
}

UniformRealDistrDecl::~UniformRealDistrDecl() {
}

std::shared_ptr<ir::Expr> UniformRealDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2 || args[0] == nullptr || args[1] == nullptr)
    return nullptr;

  auto int_ty = fact->getTy(ir::IRConstString::INT);
  auto dbl_ty = fact->getTy(ir::IRConstString::DOUBLE);
  // Note: We both accept NON-NEGATIVE integer and double
  if (args[0]->getTyp() != dbl_ty && args[0]->getTyp() != int_ty)
    return nullptr;
  if (args[1]->getTyp() != dbl_ty && args[1]->getTyp() != int_ty)
    return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(dbl_ty);
  ret->processArgRandomness();
  ret->setRandom(true);
  return ret;
}

}
}
