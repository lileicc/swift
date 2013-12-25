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

  const Ty * getRetTyp() const;
  const std::string& getName() const;
  const std::shared_ptr<Clause> getBody() const;
  void setBody(std::shared_ptr<Clause> b);
  size_t argSize() const;
  void addArg(std::shared_ptr<VarDecl> v);
  void addArgs(const std::vector<std::shared_ptr<VarDecl>>& a);
  const std::shared_ptr<VarDecl> getArg(int k) const;
  const std::vector<std::shared_ptr<VarDecl> >& getArgs() const;
  bool isRand() const;
  bool isFixed() const;

  std::string toSignature() const;

private:
  std::string name;
  std::vector<std::shared_ptr<VarDecl> > args;
  const Ty* retTyp;
  bool isrand;
  std::shared_ptr<Clause> body;
};

}
}