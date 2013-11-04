#pragma once

#include <string>
#include <vector>

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class FuncDefn {
public:
  FuncDefn(bool isrand, const std::string& name, Ty* retTyp);
  virtual ~FuncDefn();

  Ty* getRetTyp();
  const std::string& getName();
  Clause* getBody();
  void setBody(Clause* b);
  size_t argSize();
  VarDecl* getArg(int k);
  const std::vector<VarDecl*>& getArgs();
  bool isRand();
  bool isFixed();

private:
  std::string name;
  std::vector<VarDecl*> args;
  Ty* retTyp;
  bool isrand;
  Clause* body;
};

}
}