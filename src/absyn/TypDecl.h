/*
 * TypDecl.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include<vector>

#include "Decl.h"
#include "Symbol.h"

namespace swift {
namespace absyn {

class TypDecl: public Decl {
  Symbol arg;
public:
  TypDecl(int l, int c, Symbol arg);
  virtual ~TypDecl();

  const Symbol& get();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
