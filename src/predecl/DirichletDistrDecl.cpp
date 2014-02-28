#include "DirichletDistrDecl.h"

#include "../ir/ArrayTy.h"
#include "../ir/DoubleLiteral.h"
#include "../ir/IntLiteral.h"

namespace swift {
namespace predecl {
DirichletDistrDecl::DirichletDistrDecl() :
    PreDecl(std::string("Dirichlet")) {
}

DirichletDistrDecl::~DirichletDistrDecl() {
}

std::shared_ptr<ir::Expr> DirichletDistrDecl::getNew(
    std::vector<std::shared_ptr<ir::Expr>>& args,
    fabrica::TypeFactory* fact) const {
  // Type Checking
  if (args.size() < 1)
    return nullptr;

  // Two Kinds of Accepted Arguments
  //   1. vector<double>
  //   2. all double type
  // check vector<double>
  auto dbl = fact->getTy(ir::IRConstString::DOUBLE);
  auto ary_dbl = fact->getUpdateTy(new ir::ArrayTy(dbl, 1));
  if (args.size() == 1 && args[0]->getTyp() != ary_dbl) {
    auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
    ret->setArgs(args);
    ret->setTyp(ary_dbl);
    ret->processArgRandomness();
    return ret;
  }
  
  // check all double arguments
  bool okay = true;
  for (auto a : args) {
    if (a->getTyp() != dbl) {
      okay = false;
      break;
    }
  }
  if (okay) {
    auto ret = std::make_shared<ir::Distribution>(this->getName(), this);
    auto arg_n = std::make_shared<ir::IntLiteral>(args.size());
    // Note: we need to set ret type for the new argument
    arg_n->setTyp(fact->getTy(ir::IRConstString::INT));
    args.insert(args.begin(), arg_n);
    ret->setArgs(args);
    ret->setTyp(ary_dbl);
    ret->processArgRandomness();
    return ret;
  }
  return nullptr;
}

}
}
