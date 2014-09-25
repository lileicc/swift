#include "ToMatrixFuncDecl.h"

#include <vector>

#include "../ir/ArrayTy.h"
#include "../ir/FunctionCall.h"
#include "../ir/IntLiteral.h"
#include "../ir/OprExpr.h"
#include "../predecl/PreDeclList.h"

namespace swift {
namespace predecl {
ToMatrixFuncDecl::ToMatrixFuncDecl() :
    PreDecl(std::string("ToMatrix")) {
}

ToMatrixFuncDecl::~ToMatrixFuncDecl() {
}

std::shared_ptr<ir::Expr> ToMatrixFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  auto int_ty = fact->getTy(ir::IRConstString::INT);
  auto dbl_ty = fact->getTy(ir::IRConstString::DOUBLE);
  auto bool_ty = fact->getTy(ir::IRConstString::BOOL);
  auto ts_ty = fact->getTy(ir::IRConstString::TIMESTEP);
  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);
  auto str_ty = fact->getTy(ir::IRConstString::STRING);

  auto ty = args[0]->getTyp();
  if (ty == NULL) return nullptr;
  if (ty == mat_ty) return args[0];

  if (dynamic_cast<const ir::ArrayTy*>(ty) != NULL) {
    auto arr_ty = dynamic_cast<const ir::ArrayTy*>(ty);
    if (arr_ty->getDim() > 2) return nullptr;
    auto base = arr_ty->getBase();
    // check whether baseTy is numerical
    if (base != int_ty && base != dbl_ty && base != ts_ty && base != bool_ty)
      return nullptr;
  }

  if (ty == str_ty || dynamic_cast<const ir::ArrayTy*>(ty) != NULL) {
    auto func = std::make_shared<ir::FunctionCall>(this);
    func->setArgs(args);

    // check randomness
    func->setRandom(func->get(0)->isRandom());

    func->setTyp(mat_ty);

    return func;
  }

  // Otherwise, it must be numerical type
  if (ty != int_ty && ty != dbl_ty && ty != ts_ty && ty != bool_ty)
    return nullptr;

  std::vector<std::shared_ptr<ir::Expr>> ones_args{std::make_shared<ir::IntLiteral>(1)};
  auto ones = predecl::PreDeclList::onesFuncDecl.getNew(ones_args, fact);
  auto expr = std::make_shared<ir::OprExpr>(ir::IRConstant::MUL);
  expr->addArg(args[0]);
  expr->addArg(ones);
  expr->setRandom(args[0]->isRandom());
  expr->setTyp(mat_ty);
  return expr;
}

}
}
