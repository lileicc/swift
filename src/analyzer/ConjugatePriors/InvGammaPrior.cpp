/*
 * InvGammaPrior.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: yiwu
 */

#include "InvGammaPrior.h"

#include "../../ir/IRHeader.h"

namespace swift {
namespace analyzer {
namespace conjugate {

InvGammaPrior::InvGammaPrior()
  : ConjugatePrior("InvGamma") {
}

std::shared_ptr<ir::Expr> InvGammaPrior::process(
    std::shared_ptr<ir::FuncDefn> fun,
    std::set<std::shared_ptr<ir::FuncDefn>> child) 
{
  if(child.size() == 0) return std::dynamic_pointer_cast<ir::Expr>(fun->getBody());
  if(child.size() > 1) return nullptr; // currently not support!

  /*
   * x ~ InvGamma(alpha, beta)
   * y ~ Gaussian( ~ , x)
   * post(x) ~ InvGamma()
   */
  auto ch = *child.begin();
  auto gss = std::dynamic_pointer_cast<ir::Distribution>(ch->getBody());
  if (gss == nullptr) return nullptr;
  if (gss->getDistrName() != "Gaussian" || gss->getArgs().size() != 2) return nullptr;

  auto sigma = gss->get(1);
  auto ref = std::dynamic_pointer_cast<ir::FunctionCall>(sigma);
  if (ref == nullptr || ref->getRefer() != fun) return nullptr;

  // Conjugate Prior!!!
  // TODO:
  return nullptr;
}

}
}
} /* namespace swift */
