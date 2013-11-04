#include "FuncDefn.h"

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

}
}