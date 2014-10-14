#include "SetAggrFuncDecl.h"

#include <vector>

#include "../ir/SetTy.h"
#include "../ir/FunctionCall.h"

namespace swift {
namespace predecl {
SetAggrFuncDecl::SetAggrFuncDecl(std::string name) :
    PreDecl(name) {
}

SetAggrFuncDecl::~SetAggrFuncDecl() {
}

std::shared_ptr<ir::Expr> SetAggrFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr || args[0]->getTyp() == NULL)
    return nullptr;
  auto arg_ty = dynamic_cast<const ir::SetTy*>(args[0]->getTyp());
  if (arg_ty == NULL) 
    return nullptr;

  // TODO: to support general aggregation function for SetExpr
  auto base_ty = arg_ty->getRefer();

  auto func = std::make_shared<ir::FunctionCall>(this);
  func->addArg(args[0]);

  // check randomness
  func->setRandom(func->get(0)->isRandom());

  func->setTyp(base_ty);

  return func;
}

}
}
