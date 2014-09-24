#include "MatrixMatrixFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"

namespace swift {
namespace predecl {
MatrixMatrixFuncDecl::MatrixMatrixFuncDecl(std::string name) :
    PreDecl(name) {
}

MatrixMatrixFuncDecl::~MatrixMatrixFuncDecl() {
}

std::shared_ptr<ir::Expr> MatrixMatrixFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);

  // Note: We accept Int/Real/Matrix
  if (args[0]->getTyp() != mat_ty)
    return nullptr;

  auto func = std::make_shared<ir::FunctionCall>(this);

  func->addArg(args[0]);

  // check randomness
  func->setRandom(func->get(0)->isRandom());
  func->setTyp(mat_ty);

  return func;
}

}
}
