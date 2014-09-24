#include "UniformVectorDistrDecl.h"

namespace swift {
namespace predecl {
UniformVectorDistrDecl::UniformVectorDistrDecl() :
    PreDecl(std::string("UniformVector")) {
}

UniformVectorDistrDecl::~UniformVectorDistrDecl() {
}

std::shared_ptr<ir::Expr> UniformVectorDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() < 1 || args.size() > 2)
    return nullptr;

  // Note: We only accept matrix as arguments
  auto matrx = fact->getTy(ir::IRConstString::MATRIX);
  for (auto& a : args) {
    if (a == nullptr || a->getTyp() != matrx)
      return nullptr;
  }

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::MATRIX));
  ret->processArgRandomness();
  ret->setRandom(true);
  return ret;
}

}
}
