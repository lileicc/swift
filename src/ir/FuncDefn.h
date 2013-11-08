#pragma once

#include <string>
#include <vector>
#include <memory>
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class FuncDefn {
public:
  FuncDefn(bool isrand, const std::string& name, const Ty* retTyp);
  virtual ~FuncDefn();

  const std::shared_ptr<Ty> getRetTyp() const;
  const std::string& getName() const;
  std::shared_ptr<Clause> getBody() const;
  void setBody(Clause* b);
  size_t argSize() const;
  void addArg(std::shared_ptr<VarDecl> v);
  std::shared_ptr<VarDecl> getArg(int k) const;
  const std::vector<std::shared_ptr<VarDecl> >& getArgs() const;
  bool isRand() const;
  bool isFixed() const;

  std::string toSignature() const;

private:
  std::string name;
  std::vector<std::shared_ptr<VarDecl> > args;
  std::shared_ptr<Ty> retTyp;
  bool isrand;
  std::shared_ptr<Clause> body;
};

}
}
