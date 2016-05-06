#include "MatrixConstructFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"

namespace swift {
namespace predecl {
MatrixConstructFuncDecl::MatrixConstructFuncDecl(std::string name) :
    PreDecl(name) {
}

MatrixConstructFuncDecl::~MatrixConstructFuncDecl() {
}

std::shared_ptr<ir::Expr> MatrixConstructFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2)
    return nullptr;

  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);
  auto int_ty = fact->getTy(ir::IRConstString::INT);

  // Note: We accept Int/Real/Matrix
  if (args[0]->getTyp() != int_ty || args[1]->getTyp() != int_ty)
    return nullptr;

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
