#include "BooleanDistrDecl.h"

#include "../ir/DoubleLiteral.h"
#include "../ir/BoolLiteral.h"

namespace swift {
namespace predecl {
BooleanDistrDecl::BooleanDistrDecl() :
    PreDecl(std::string("BooleanDistrib")) {
}

BooleanDistrDecl::~BooleanDistrDecl() {
}

std::shared_ptr<ir::Expr> BooleanDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  // Note: We only accept double
  if (args[0]->getTyp() != fact->getTy(ir::IRConstString::DOUBLE))
    return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::BOOL));
  return ret;
}

}
}
