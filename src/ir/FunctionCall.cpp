#include "FunctionCall.h"

#include "FuncDefn.h"
#include "IRConst.h"

#include "../predecl/PreDecl.h"

namespace swift {
namespace ir {

// init for builtin functions
FunctionCall::FunctionCall(const predecl::PreDecl* refer) :
    refer(nullptr), istmp(false), tmparg(nullptr), builtin(refer), funcName(""), kind(IRConstant::FIXED) {
}

FunctionCall::FunctionCall(std::string name) :
    refer(nullptr), istmp(false), tmparg(nullptr), builtin(NULL), funcName(name), kind(IRConstant::FIXED) {
}

FunctionCall::FunctionCall(std::shared_ptr<FuncDefn> refer) :
    refer(refer), istmp(false), tmparg(nullptr), builtin(NULL), funcName("") {
  if (refer == nullptr)
    kind = IRConstant::NA;
  else {
    if (refer->isRand())
      kind = IRConstant::RANDOM;
    if (refer->isFixed())
      kind = IRConstant::FIXED;
  }
}

FunctionCall::~FunctionCall() {

}

const predecl::PreDecl* FunctionCall::getBuiltinRefer() const {
  return builtin;
}

bool FunctionCall::isBuiltin() const {
  return builtin != NULL || funcName.size() > 0;
}

IRConstant FunctionCall::getKind() const {
  return kind;
}

std::shared_ptr<FuncDefn> FunctionCall::getRefer() const {
  return refer;
}

std::string FunctionCall::getName() const {
  if (funcName.size() > 0) return funcName;
  if (builtin != NULL) return builtin->getName();
  if (refer != nullptr) return refer->getName();
  return "";
}

bool FunctionCall::isTemporal() const {
  return istmp;
}

std::shared_ptr<Expr> FunctionCall::getTemporalArg() {
  return tmparg;
}

// Note that we only process the first timestep ty
void FunctionCall::processTemporal(const Ty* timety) {
  for (size_t i = 0; i < args.size(); ++i) {
    if (args[i]->getTyp() == timety) {
      istmp = true;
      tmparg = args[i];
      args.erase(args.begin() + i);
      break;
    }
  }
}

void FunctionCall::print(FILE* file, int indent) const {
  fprintf(file, "%*sFunctionCall:\n", indent, "");
  fprintf(file, "%*sfun: %s\n", indent + 2, "", (refer != nullptr ? refer->toSignature().c_str() : ("[built-in] " + getName()).c_str()));
  if (tmparg != nullptr) {
    fprintf(file, "%*stemp_args:\n", indent + 2, "");
    tmparg->print(file, indent + 4);
  }
  if (argSize()) {
    fprintf(file, "%*sargs:\n", indent + 2, "");
    for (size_t i = 0; i < argSize(); i++) {
      if (get(i) != nullptr) {
        get(i)->print(file, indent + 4);
      }
    }
  }
}

std::string FunctionCall::toString() {
  std::string ret = (refer != nullptr ? refer->getName() : getName()) + "(";
  bool mark = false;
  if (tmparg != nullptr) {
    ret.append(tmparg->toString());
    mark = true;
  }
  for (size_t i = 0; i < argSize(); ++i) {
    if (mark) ret.push_back(',');
    else mark=true;
    if (get(i)!=nullptr)
      ret.append(get(i)->toString());
  }
  ret.push_back(')');
  return ret;
}

}
}
