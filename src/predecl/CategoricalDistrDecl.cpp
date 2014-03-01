#include "CategoricalDistrDecl.h"
#include "../ir/CategoricalDistr.h"
#include "../ir/MapTy.h"
#include "../ir/MapExpr.h"
#include "../ir/DoubleLiteral.h"
#include "../ir/ConstSymbol.h"

namespace swift {
namespace predecl {
CategoricalDistrDecl::CategoricalDistrDecl() :
    PreDecl(std::string("Categorical")) {
}

CategoricalDistrDecl::~CategoricalDistrDecl() {
}

std::shared_ptr<ir::Expr> CategoricalDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0]->getTyp() == NULL
      || args[0]->getTyp()->getTyp() != ir::IRConstant::MAP)
    return nullptr;
  const ir::MapTy* ty = (const ir::MapTy*) (args[0]->getTyp());
  if (ty->getTo() != fact->getTy(ir::IRConstString::DOUBLE))
    return nullptr;
  if (ty->getFrom() == NULL)
    return nullptr;
  std::shared_ptr<ir::MapExpr> m = std::dynamic_pointer_cast<ir::MapExpr>(
      args[0]);
  if (m == nullptr)
    return nullptr;

  // TODO:
  // Currently, We ONLY Allow [ constant symbold -> double_literal ]
  std::shared_ptr<ir::CategoricalDistr> ret = std::make_shared<
      ir::CategoricalDistr>(this);
  for (size_t i = 0; i < m->mapSize(); ++i) {
    std::shared_ptr<ir::ConstSymbol> x = std::dynamic_pointer_cast<
        ir::ConstSymbol>(m->getFrom(i));
    std::shared_ptr<ir::DoubleLiteral> y = std::dynamic_pointer_cast<
        ir::DoubleLiteral>(m->getTo(i));
    if (x == nullptr || y == nullptr)
      return nullptr;
    ret->addWeight(y->getValue());
    ret->addSymbol(x);
  }
  ret->addArg(m);
  ret->setTyp(ty->getTo());
  ret->processArgRandomness();
  return ret;
}

}
}
