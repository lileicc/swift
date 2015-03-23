#include "MatrixSubsetFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"

namespace swift {
namespace predecl {
MatrixSubsetFuncDecl::MatrixSubsetFuncDecl(std::string name, int n_args) :
    PreDecl(name), n_args(n_args) {
}

MatrixSubsetFuncDecl::~MatrixSubsetFuncDecl() {
}

std::shared_ptr<ir::Expr> MatrixSubsetFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if ((int)args.size() != n_args + 1)
    return nullptr;
  for (auto& a : args) {
    if (a == nullptr || a->getTyp() == NULL)
      return nullptr;
  }

  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);
  auto int_ty = fact->getTy(ir::IRConstString::INT);

  if (args[0]->getTyp() != mat_ty)
    return nullptr;
  for (size_t i = 1; i < args.size(); ++i) {
    if (args[i]->getTyp() != int_ty)
      return nullptr;
  }

  auto func = std::make_shared<ir::FunctionCall>(this);

  func->setArgs(args);

  // check randomness
  for (auto& a : args) {
    if (a->isRandom())
      func->setRandom(true);
  }
  func->setTyp(mat_ty);

  return func;
}

}
}
