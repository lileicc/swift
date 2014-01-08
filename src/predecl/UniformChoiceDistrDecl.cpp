#include "UniformChoiceDistrDecl.h"
#include "../ir/SetTy.h"
#include "../ir/SetExpr.h"
#include "../ir/UniformChoiceDistr.h"

namespace swift { namespace predecl {
UniformChoiceDistrDecl::UniformChoiceDistrDecl()
  :PreDeclDistr(std::string("UniformChoice")){
}

UniformChoiceDistrDecl::~UniformChoiceDistrDecl() {
}

std::shared_ptr<ir::Distribution> UniformChoiceDistrDecl::getNew
  (std::vector<std::shared_ptr<ir::Expr>>& args, fabrica::TypeFactory* fact) const {
  if (args.size() != 1 || args[0]->getTyp() == NULL || args[0]->getTyp()->getTyp() != ir::IRConstant::SET)
    return nullptr;
  auto e = std::dynamic_pointer_cast<ir::SetExpr>(args[0]);
  if (e == nullptr) return nullptr;
  auto ptr = std::make_shared<ir::UniformChoiceDistr>(e);
  auto ty = (const ir::SetTy*)(e->getTyp());
  ptr->setArgs(args);
  ptr->setTyp(ty->getRefer());
  return ptr;
}

}
}
