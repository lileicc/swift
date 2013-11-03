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
  Symbol func;
  Symbol arg;
  Symbol typ;
public:
  OriginDecl(int l, int c, Symbol typ, Symbol func, Symbol arg);
  virtual ~OriginDecl();

  Symbol& getFunc();
  Symbol& getArg();
  Symbol& getTyp();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
