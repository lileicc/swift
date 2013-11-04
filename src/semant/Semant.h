/*
 * Semant.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include <cstdlib>
#include <cstdio>
#include "../absyn/BlogProgram.h"
#include "../msg/ErrorMsg.h"
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
  void error(int line, int col, std::string info);
  TypeFactory tyFactory;
  msg::ErrorMsg errorMsg;
};

}
} /* namespace swift */
