#include "FuncDefn.h"

#include "Ty.h"
#include "VarDecl.h"

namespace swift { namespace ir {
 
FuncDefn::FuncDefn(bool isrand, const std::string& name, const Ty* retTyp)
  :name(name), retTyp(retTyp), isrand(isrand), body(NULL) {
}

FuncDefn::~FuncDefn() {
}

const Ty* FuncDefn::getRetTyp() const {
  return retTyp;
}

const std::string& FuncDefn::getName() const {
  return name;
}

const std::shared_ptr<Clause> FuncDefn::getBody() const {
  return body;
}

void FuncDefn::setBody(std::shared_ptr<Clause> b) {
  body = b;
}

size_t FuncDefn::argSize() const {
  return args.size();
}

void FuncDefn::addArgs(const std::vector<std::shared_ptr<VarDecl>>& a) {
  args = a;
}

void FuncDefn::addArg(const std::shared_ptr<VarDecl> v) {
  args.push_back(v);
}

const std::shared_ptr<VarDecl> FuncDefn::getArg(int k) const {
  return args[k];
}

const std::vector<std::shared_ptr<VarDecl> >& FuncDefn::getArgs() const {
  return args;
}

bool FuncDefn::isRand() const {
  return isrand;
}

bool FuncDefn::isFixed() const {
  return !isrand;
}

std::string FuncDefn::toSignature() const {
  std::string ret;
  ret.append(retTyp == NULL ? "NULL" : retTyp->toString());
  ret.push_back(' ');
  ret.append(name);
  ret.push_back('(');
  for (size_t i = 0; i < args.size(); i++)  {
    if (i > 0) ret.push_back(',');
    ret.append(args[i]->toString());
  }
  ret.push_back(')');
  return ret;
}

}
}