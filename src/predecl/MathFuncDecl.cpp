#include "MathFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"

namespace swift {
namespace predecl {
MathFuncDecl::MathFuncDecl(std::string name) :
    PreDecl(name) {
}

MathFuncDecl::~MathFuncDecl() {
}

std::shared_ptr<ir::Expr> MathFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  auto int_ty = fact->getTy(ir::IRConstString::INT);
  auto real_ty = fact->getTy(ir::IRConstString::DOUBLE);
  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);

  // Note: We accept Int/Real/Matrix
  if (args[0]->getTyp() != int_ty
    && args[0]->getTyp() != real_ty
    && args[0]->getTyp() != mat_ty)
    return nullptr;

  auto ret_ty = (args[0]->getTyp() == mat_ty ? mat_ty : real_ty);

  auto func = std::make_shared<ir::FunctionCall>(this);

  func->addArg(args[0]);

  // check randomness
  func->setRandom(func->get(0)->isRandom());
  func->setTyp(ret_ty);

  return func;
}

}
}
