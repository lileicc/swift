#include "LoadRealMatrixFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"

namespace swift {
namespace predecl {
LoadRealMatrixFuncDecl::LoadRealMatrixFuncDecl() :
    PreDecl(std::string("loadRealMatrix")) {
}

LoadRealMatrixFuncDecl::~LoadRealMatrixFuncDecl() {
}

std::shared_ptr<ir::Expr> LoadRealMatrixFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);
  auto int_ty = fact->getTy(ir::IRConstString::INT);
  auto str_ty = fact->getTy(ir::IRConstString::STRING);
  if (args.size() < 1 || args[0] == nullptr || args[0]->getTyp() != str_ty)
    return nullptr;
  for (size_t i = 1; i < args.size(); ++i) {
    if (args[i] == nullptr || args[i]->getTyp() != int_ty)
      return nullptr;
  }
  if (args.size() > 5) return nullptr;
  if (args.size() == 4) return nullptr;

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
