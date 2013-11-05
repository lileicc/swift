#include "FuncDefn.h"

#include "Ty.h"
#include "VarDecl.h"

namespace swift { namespace ir {
 
FuncDefn::FuncDefn(bool isrand, const std::string& name, Ty* retTyp)
  :name(name), retTyp(retTyp), isrand(isrand), body(NULL) {
}

FuncDefn::~FuncDefn() {
}

Ty* FuncDefn::getRetTyp() {
  return retTyp;
}

const std::string& FuncDefn::getName() {
  return name;
}

Clause* FuncDefn::getBody() {
  return body;
}

void FuncDefn::setBody(Clause* b) {
  body = b;
}

size_t FuncDefn::argSize() {
  return args.size();
}

void FuncDefn::addArg(VarDecl* v) {
  args.push_back(v);
}

VarDecl* FuncDefn::getArg(int k) {
  return args[k];
}

const std::vector<VarDecl*>& FuncDefn::getArgs() {
  return args;
}

bool FuncDefn::isRand() {
  return isrand;
}

bool FuncDefn::isFixed() {
  return !isrand;
}

std::string FuncDefn::toSignature() {
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