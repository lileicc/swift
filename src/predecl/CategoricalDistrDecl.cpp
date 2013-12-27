#include "CategoricalDistrDecl.h"
#include "../ir/CategoricalDistr.h"
#include "../ir/MapTy.h"
#include "../ir/MapExpr.h"
#include "../ir/DoubleLiteral.h"
#include "../ir/ConstSymbol.h"

namespace swift { namespace predecl {
CategoricalDistrDecl::CategoricalDistrDecl()
  :PreDeclDistr(std::string("Categorical")){
}

CategoricalDistrDecl::~CategoricalDistrDecl() {
}

std::shared_ptr<ir::Distribution> CategoricalDistrDecl::getNew
  (std::vector<std::shared_ptr<ir::Expr>>& args, fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0]->getTyp() == NULL || args[0]->getTyp()->getTyp() != ir::IRConstant::MAP) return nullptr;
  const ir::MapTy* ty = (const ir::MapTy*) (args[0]->getTyp());
  if (ty->getFrom() != fact->getTy(ir::IRConstString::DOUBLE)) return nullptr;
  if (ty->getTo() == NULL) return nullptr;
  std::shared_ptr<ir::MapExpr> m = std::dynamic_pointer_cast<ir::MapExpr>(args[0]);
  if (m == nullptr) return nullptr;
  // TODO:
  // Currently, We ONLY Allow [ double_literal -> constant symbol ]
  std::shared_ptr<ir::CategoricalDistr> ret = std::make_shared<ir::CategoricalDistr>(this);
  for (size_t i = 0; i < m->argSize(); ++i) {
    std::shared_ptr<ir::DoubleLiteral> x = std::dynamic_pointer_cast<ir::DoubleLiteral>(m->getFrom(i));
    std::shared_ptr<ir::ConstSymbol> y = std::dynamic_pointer_cast<ir::ConstSymbol>(m->getTo(i));
    if (x == nullptr || y == nullptr) return nullptr;
    ret->addWeight(x->getValue());
    ret->addSymbol(y);
  }
  ret->setTyp(ty->getTo());
  return ret;
}

}
}