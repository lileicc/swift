/*
 * InvGammaPrior.h
 *
 *  Created on: Apr 30, 2015
 *      Author: yiwu
 */

#pragma once

#include "ConjugatePrior.h"

namespace swift {
namespace analyzer {
namespace conjugate {

class InvGammaPrior: public ConjugatePrior{
public:
  InvGammaPrior();
  
  virtual std::shared_ptr<ir::Expr> process(
    std::shared_ptr<ir::FuncDefn> fun,
    std::set<std::shared_ptr<ir::FuncDefn>> child);

private:
};

}
}
} /* namespace swift */
