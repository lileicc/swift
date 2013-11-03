/*
 * Semant.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include "../absyn/BlogProgram.h"

namespace swift {
namespace semant {

class Semant {
public:
  Semant();
  ~Semant();
  void process(absyn::BlogProgram *prog);
private:
  void transExpr(absyn::Expr* expr);
  void transExpr(absyn::OpExpr* expr);
};

}
} /* namespace swift */
