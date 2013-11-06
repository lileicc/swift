#pragma once

#include <string>
#include <vector>

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class FuncDefn {
public:
  FuncDefn(bool isrand, const std::string& name, const Ty* retTyp);
  virtual ~FuncDefn();

  const Ty* getRetTyp() const;
  const std::string& getName() const;
  Clause* getBody() const;
  void setBody(Clause* b);
  size_t argSize() const;
  void addArg(VarDecl* v);
  const VarDecl* getArg(int k) const;
  const std::vector<VarDecl*>& getArgs() const;
  bool isRand() const;
  bool isFixed() const;

  std::string toSignature() const;

private:
  std::string name;
  std::vector<VarDecl*> args;
  const Ty* retTyp;
  bool isrand;
  Clause* body;
};

}
}
