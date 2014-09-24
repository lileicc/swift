#include "ToIntFuncDecl.h"

#include <vector>

#include "../ir/FunctionCall.h"
#include "../predecl/PreDeclList.h"

namespace swift {
namespace predecl {
ToIntFuncDecl::ToIntFuncDecl() :
    PreDecl(std::string("toInt")) {
}

ToIntFuncDecl::~ToIntFuncDecl() {
}

std::shared_ptr<ir::Expr> ToIntFuncDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() != 1 || args[0] == nullptr)
    return nullptr;

  auto int_ty = fact->getTy(ir::IRConstString::INT);
  auto dbl_ty = fact->getTy(ir::IRConstString::DOUBLE);
  auto str_ty = fact->getTy(ir::IRConstString::STRING);
  auto bool_ty = fact->getTy(ir::IRConstString::BOOL);
  auto ts_ty = fact->getTy(ir::IRConstString::TIMESTEP);
  auto mat_ty = fact->getTy(ir::IRConstString::MATRIX);

  auto ty = args[0]->getTyp();
  if (ty != NULL) {
    // Special Treatment for NameTy
    if (ty->getTyp() == ir::IRConstant::NAMETY) {
      // In our current model, all the instances will be represented by a integer internally
      args[0]->setTyp(int_ty);
      return args[0];
    }
    if (ty == int_ty)
      return args[0]; // No type conversion required
    if (ty != dbl_ty && ty != str_ty && ty != bool_ty && ty != ts_ty && ty != mat_ty)
      return nullptr; // Type Checking failure
    // Special check for matrix-type
    if (ty == mat_ty) {
      auto mat = predecl::PreDeclList::asScalarFuncDecl.getNew(args, fact);
      args.clear();
      args.push_back(mat);
    }
  }

  auto func = std::make_shared<ir::FunctionCall>(this);
  func->setArgs(args);

  // check randomness
  func->setRandom(func->get(0)->isRandom());

  func->setTyp(int_ty);

  return func;
}

}
}
