#include "MatrixStackFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
MatrixStackFuncDecl::MatrixStackFuncDecl(std::string name) :
    PreDecl(name) {
}

MatrixStackFuncDecl::~MatrixStackFuncDecl() {
}

std::shared_ptr<ir::Expr> MatrixStackFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  auto mtrx = fact->getTy(ir::IRConstString::MATRIX);
  auto dbl_ty = fact->getTy(ir::IRConstString::DOUBLE);
  auto int_ty = fact->getTy(ir::IRConstString::INT);
  bool has_matrix = false, has_double = false;
  for (auto& a : args) {
    if (a == nullptr)
      return nullptr;
    if (a->getTyp() == mtrx) {
      if (has_double) return nullptr;
      has_matrix = true;
    } else
    if (a->getTyp() == dbl_ty || a->getTyp() == int_ty) {
      if (has_matrix) return nullptr;
      has_double = true;
    } else 
      return nullptr;
  }
  if (args.size() < 1) return nullptr;
  if (args.size() == 1 && has_matrix) return args[0];

  auto func = std::make_shared<ir::FunctionCall>(this);

  func->setArgs(args);

  // check randomness
  for (auto a : args) {
    if (a->isRandom()) {
      func->setRandom(true);
      break;
    }
  }
  func->setTyp(mtrx);

  return func;
}

}
}
