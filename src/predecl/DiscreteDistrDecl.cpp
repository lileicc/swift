#include "DiscreteDistrDecl.h"

#include "../ir/ArrayTy.h"
#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
DiscreteDistrDecl::DiscreteDistrDecl() :
    PreDecl(std::string("Discrete")) {
}

DiscreteDistrDecl::~DiscreteDistrDecl() {
}

std::shared_ptr<ir::Expr> DiscreteDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  // Note: We only accept array<double>
  auto dbl = fact->getTy(ir::IRConstString::DOUBLE);
  auto ary_dbl = fact->getUpdateTy(new ir::ArrayTy(dbl, 1));
  if (args[0]->getTyp() != ary_dbl)
    return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::INT));
  ret->processArgRandomness();
  return ret;
}

}
}
