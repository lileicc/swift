#include "PrevFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"
#include "../ir/TimestepLiteral.h"
#include "../ir/IntLiteral.h"

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

  auto func = std::make_shared<ir::FunctionCall>(this);

  //Special Check for Multiple Prev()
  //  i.e. Prev(Prev(t, 1), 1) :::==> Prev(t, 2)
  auto sub = std::dynamic_pointer_cast<ir::FunctionCall>(args[0]);
  if (sub->isBuiltin() && sub->getBuiltinRefer() == this && sub->argSize() == 1
      && std::dynamic_pointer_cast<ir::IntLiteral>(sub->get(0)) != nullptr) {
    auto val = std::dynamic_pointer_cast<ir::IntLiteral>(sub->get(0));
    func->addArg(sub->getTemporalArg());
    func->addArg(std::make_shared<ir::IntLiteral>(val->getValue() + 1));
  }
  else {
    func->addArg(args[0]);
    func->addArg(std::make_shared<ir::IntLiteral>(1));
  }

  func->processTemporal(ts_ty);
  func->setTyp(ts_ty);
  // check randomness
  func->setRandom(func->get(0)->isRandom());

  return func;
}

}
}
