/*
 * VarRef.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"
#include "Symbol.h"

namespace swift {
namespace absyn {

class VarRef: public Expr {
  Symbol var;
public:
  VarRef(int l, int c, Symbol var);
  virtual ~VarRef();

  const Symbol& getVar();

  // For Debugging Use
  void print(FILE* file, int indent);
  std::string toString();

  Expr* clone();
};

}
}
