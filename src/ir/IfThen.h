/*
 * IfThen.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#pragma once

#include "Clause.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class IfThen: public Clause {
public:
  IfThen(std::shared_ptr<Expr> cond = nullptr,
        std::shared_ptr<Clause> thcl = nullptr,
        std::shared_ptr<Clause> elcl = nullptr);
  ~IfThen();

  void setCond(std::shared_ptr<Expr> e);
  void setThen(std::shared_ptr<Clause> c);
  void setElse(std::shared_ptr<Clause> c);
  std::shared_ptr<Expr> getCond() const;
  std::shared_ptr<Clause> getThen() const;
  std::shared_ptr<Clause> getElse() const;

private:
  std::shared_ptr<Expr> cond;
  std::shared_ptr<Clause> thcl;
  std::shared_ptr<Clause> elcl;
};

}
}
