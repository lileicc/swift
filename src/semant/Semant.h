/*
 * Semant.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include "../absyn/BlogProgram.h"
#include "TypeFactory.h"

namespace swift {
namespace semant {

class Semant {
public:
  Semant();
  ~Semant();
  void process(absyn::BlogProgram *prog);
private:
  void processTypes(absyn::BlogProgram *prog);
  void transExpr(absyn::Expr* expr);
  void transExpr(absyn::OpExpr* expr);
  void transExpr(absyn::FuncApp* expr);
  void transTyDecl(absyn::TypDecl* td);
  TypeFactory tyFactory;
};

}
} /* namespace swift */
