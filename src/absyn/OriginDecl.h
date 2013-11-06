/*
 * OriginDecl.h
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#pragma once

#include "Decl.h"
#include "Symbol.h"

namespace swift {
namespace absyn {

class OriginDecl: public Decl {
public:
  OriginDecl(int l, int c, Symbol typ, Symbol func, Symbol arg);
  virtual ~OriginDecl();

  const Symbol& getFunc() const;
  const Symbol& getArg() const;
  const Symbol& getTyp() const;

  // For Debugging Use
  void print(FILE* file, int indent);
private:
  Symbol typ;
  Symbol func;
  Symbol arg;
};

}
}
