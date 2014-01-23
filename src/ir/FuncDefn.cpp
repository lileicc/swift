#include "FuncDefn.h"

#include "Ty.h"
#include "VarDecl.h"
#include "Clause.h"
#include <iostream>
using namespace std;

namespace swift { namespace ir {
 
FuncDefn::FuncDefn(bool isrand, const std::string& name, const Ty* retTyp)
  :name(name), retTyp(retTyp), isrand(isrand), body(nullptr) {
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

void FuncDefn::setArgs(const std::vector<std::shared_ptr<VarDecl>>& a) {
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
  ret.append(name);
  ret.push_back('(');
  for (size_t i = 0; i < args.size(); i++)  {
    if (i > 0) ret.push_back(',');
    ret.append(args[i]->toSignature());
  }
  ret.push_back(')');
  return ret;
}

void FuncDefn::print(FILE* file, int indent){
  fprintf(file, "%*s(FuncDefn:\n", indent, "");
  fprintf(file, "%*s%s\n", indent+2, "", toSignature().c_str());
  fprintf(file, "%*s(body:\n", indent+2, "");
  if(getBody() != nullptr){
    getBody()->print(file, indent+4);
  }
  fprintf(file, "%*s)\n", indent+2, "");
  fprintf(file, "%*s)\n", indent, "");
}

}
}
