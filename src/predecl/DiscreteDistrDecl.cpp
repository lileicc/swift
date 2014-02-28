#include "DiscreteDistrDecl.h"

#include "../ir/IntLiteral.h"
#include "../absyn/Ty.h"

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
  auto ary_dbl = fact->getTy((absyn::Ty(ir::IRConstString::BLOG_DOUBLE,1)).toString());
  if (args[0]->getTyp() != ary_dbl)
    return nullptr;

  auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
  ret->setArgs(args);
  ret->setTyp(fact->getTy(ir::IRConstString::INT));
  return ret;
}

}
}
