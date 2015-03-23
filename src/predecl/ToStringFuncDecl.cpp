#include "ToStringFuncDecl.h"

#include <vector>
#include <memory>

#include "../ir/FunctionCall.h"
#include "../ir/StringLiteral.h"
#include "../ir/OprExpr.h"

namespace swift {
namespace predecl {
ToStringFuncDecl::ToStringFuncDecl() :
    PreDecl(std::string("toString")) {
}

ToStringFuncDecl::~ToStringFuncDecl() {
}

std::shared_ptr<ir::Expr> ToStringFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  auto str_ty = fact->getTy(ir::IRConstString::STRING);
  auto ts_ty = fact->getTy(ir::IRConstString::TIMESTEP);
  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);
  auto ty = args[0]->getTyp();

  if (ty == NULL) {
    auto ret = std::make_shared<ir::StringLiteral>(std::string("NULL"));
    ret->setTyp(str_ty);
    return ret;
  }

  if (ty == str_ty) return args[0];

  // TODO: currently not support complicated type
  if (ty == mat_ty || ty->getTyp() == ir::IRConstant::ARRAY
      || ty->getTyp() == ir::IRConstant::MAP || ty->getTyp() == ir::IRConstant::SET)
      return nullptr;

  auto func = std::make_shared<ir::FunctionCall>(this);
  func->setArgs(args);

  // check randomness
  func->setRandom(func->get(0)->isRandom());

  func->setTyp(str_ty);

  if (ty == ts_ty) {
    auto opr = std::make_shared<ir::OprExpr>(ir::IRConstant::PLUS);
    opr->addArg(std::make_shared<ir::StringLiteral>(std::string("@")));
    opr->addArg(func);
    opr->setRandom(func->isRandom());
    opr->setTyp(str_ty);
    return opr;
  }
  else
    return func;
}

}
}
