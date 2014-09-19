#include "MatrixRealFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"

namespace swift {
namespace predecl {
MatrixRealFuncDecl::MatrixRealFuncDecl(std::string name) :
    PreDecl(name) {
}

MatrixRealFuncDecl::~MatrixRealFuncDecl() {
}

std::shared_ptr<ir::Expr> MatrixRealFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  auto real_ty = fact->getTy(ir::IRConstString::DOUBLE);
  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);

  // Note: We accept Int/Real/Matrix
  if (args[0]->getTyp() != mat_ty)
    return nullptr;

  auto func = std::make_shared<ir::FunctionCall>(this);

  func->addArg(args[0]);

  // check randomness
  func->setRandom(func->get(0)->isRandom());
  func->setTyp(real_ty);

  return func;
}

}
}
