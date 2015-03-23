#include "MultinomialDistrDecl.h"

#include "../ir/ArrayTy.h"
#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
MultinomialDistrDecl::MultinomialDistrDecl() :
    PreDecl(std::string("Multinomial")) {
}

MultinomialDistrDecl::~MultinomialDistrDecl() {
}

std::shared_ptr<ir::Expr> MultinomialDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() < 2)
    return nullptr;

  // accepted arguments
  //   1. int, vector<double>
  //   2. int, matrix
  // check vector<double>
  auto dbl = fact->getTy(ir::IRConstString::DOUBLE);
  auto ary_dbl = fact->getUpdateTy(new ir::ArrayTy(dbl, 1));
  auto int_ty = fact->getTy(ir::IRConstString::INT);
  auto ary_int = fact->getUpdateTy(new ir::ArrayTy(int_ty, 1));
  auto mtrx = fact->getTy(ir::IRConstString::MATRIX);
  if (args[0]->getTyp() != int_ty)
    return nullptr;
  if (args.size() == 2 && 
      (args[1]->getTyp() == ary_dbl || args[1]->getTyp() == mtrx)) {
    auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
    ret->setArgs(args);
    ret->setTyp(ary_int);
    ret->processArgRandomness();
    ret->setRandom(true);
    return ret;
  }
  return nullptr;
}

}
}
