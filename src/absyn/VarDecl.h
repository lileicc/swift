/*
 * VarDecl.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 *
 *  Note :
 *    This is not a DECL but an EXPR
 *
 */

#pragma once

#include "Expr.h"
#include "Symbol.h"
#include "Ty.h"

namespace swift {
namespace absyn {

class VarDecl: public Expr {
  Ty typ;
  Symbol var;
public:
  VarDecl(int l, int c, Ty typ, Symbol var = Symbol());
  virtual ~VarDecl();

  const Ty& getTyp() const;
  const Symbol& getVar() const;

  //For Debugging Use
  void print(FILE *file, int indent);
};

}
}
