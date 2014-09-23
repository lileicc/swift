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
  for (auto& a : args) {
    if (a == nullptr || a->getTyp() != mtrx)
      return nullptr;
  }
  if (args.size() < 1) return nullptr;
  if (args.size() == 1) return args[0];

  auto func = std::make_shared<ir::FunctionCall>(this);

  auto arg_n = std::make_shared<ir::IntLiteral>(args.size());
  // Note: we need to set ret type for the new argument
  arg_n->setTyp(fact->getTy(ir::IRConstString::INT));
  args.insert(args.begin(), arg_n);
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
