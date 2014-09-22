#include "MatrixInitFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"

namespace swift {
namespace predecl {
MatrixInitFuncDecl::MatrixInitFuncDecl(std::string name) :
    PreDecl(name) {
}

MatrixInitFuncDecl::~MatrixInitFuncDecl() {
}

std::shared_ptr<ir::Expr> MatrixInitFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 2 || args[0] == nullptr || args[1] == nullptr)
    return nullptr;

  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);
  auto int_ty = fact->getTy(ir::IRConstString::INT);

  // Note: We accept Int/Real/Matrix
  if (args[0]->getTyp() != int_ty || args[1]->getTyp() != int_ty)
    return nullptr;

  auto func = std::make_shared<ir::FunctionCall>(this);

  func->addArg(args[0]);
  func->addArg(args[1]);

  // check randomness
  func->setRandom(func->get(0)->isRandom() || func->get(1)->isRandom());
  func->setTyp(mat_ty);

  return func;
}

}
}
