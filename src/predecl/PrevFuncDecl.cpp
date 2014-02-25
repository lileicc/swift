#include "PrevFuncDecl.h"

#include <vector>

#include "../ir/OprExpr.h"
#include "../ir/TimestepLiteral.h"

namespace swift {
namespace predecl {
PrevFuncDecl::PrevFuncDecl() :
    PreDecl(std::string("Prev")) {
}

PrevFuncDecl::~PrevFuncDecl() {
}

std::shared_ptr<ir::Expr> PrevFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  auto ts_ty = fact->getTy(ir::IRConstString::TIMESTEP);

  // Note: We ONLY accept Time Literal!
  if (args[0]->getTyp() != ts_ty)
    return nullptr;

  //Special Check for Multiple Prev()
  //  i.e. Prev(Prev(t)) :::==> Prev(t - @1) :::==> t - @2
  auto sub = std::dynamic_pointer_cast<ir::OprExpr>(args[0]);
  if (sub != nullptr && sub->getOp() == ir::IRConstant::MINUS && sub->argSize() == 2
    && std::dynamic_pointer_cast<ir::TimestepLiteral>(sub->get(1)) != nullptr) {
    auto val = std::dynamic_pointer_cast<ir::TimestepLiteral>(sub->get(1));
    auto opr = std::make_shared<ir::OprExpr>(ir::IRConstant::MINUS);
    opr->addArg(sub->get(0));
    auto shft = std::make_shared<ir::TimestepLiteral>(val->getValue() + 1);
    shft->setTyp(ts_ty);
    opr->addArg(shft);
    opr->setTyp(ts_ty);
    // check randomness
    opr->setRandom(sub->get(0)->isRandom());
    return opr;
  }

  //  Current Version: Prev(t) :::==> t - @1
  auto opr = std::make_shared<ir::OprExpr>(ir::IRConstant::MINUS);
  opr->addArg(args[0]);
  auto shft = std::make_shared<ir::TimestepLiteral>(1);
  shft->setTyp(ts_ty);
  opr->addArg(shft);
  opr->setTyp(ts_ty);
  // check randomness
  opr->setRandom(args[0]->isRandom());
  return opr;
}

}
}
