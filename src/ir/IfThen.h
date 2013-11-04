/*
 * IfThen.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#pragma once

#include "IRForwardDecl.h"

#include "Clause.h"

namespace swift {
namespace ir {

class IfThen: public Clause {
public:
  IfThen(Expr* cond=NULL, Clause* thcl=NULL, Clause* elcl=NULL);
  ~IfThen();

  void setCond(Expr* e);
  void setThen(Clause *c);
  void setElse(Clause *c);
  Expr* getCond();
  Clause* getThen();
  Clause* getElse();

private:
  Expr* cond;
  Clause* thcl;
  Clause* elcl;
};

}
}
