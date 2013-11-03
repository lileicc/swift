/*
* DistinctDecl.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*/

#pragma once

#include <vector>

#include "Decl.h"
#include "Symbol.h"

namespace swift {
  namespace absyn {

class DistinctDecl :
  public Decl
{
  Symbol typ;
  std::vector<Symbol> var;
  std::vector<int> len;
public:
  DistinctDecl(int l, int c, Symbol typ);
  virtual ~DistinctDecl();

  size_t size();
  Symbol& getTyp();
  Symbol& getVar(int k);
  int getLen(int k);
  void add(Symbol v, int l = 1);

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}