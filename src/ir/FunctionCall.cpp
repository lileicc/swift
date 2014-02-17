#include "FunctionCall.h"

#include "FuncDefn.h"
#include "IRConst.h"

namespace swift {
namespace ir {

// TODO: To fix this hacking implementation for builtin functions
FunctionCall::FunctionCall(std::string name) :
    refer(nullptr), kind(IRConstant::FIXED), isbuiltin(true), builtinName(name),
    istmp(false), tmpvar(nullptr) {
}

FunctionCall::FunctionCall(std::shared_ptr<FuncDefn> refer) :
    refer(refer), istmp(false), tmpvar(nullptr) {
  if (refer == nullptr)
    kind = IRConstant::NA;
  else {
    if (refer->isRand())
      kind = IRConstant::RANDOM;
    if (refer->isFixed())
      kind = IRConstant::FIXED;
  }

  isbuiltin = false;
  builtinName.clear();
}

FunctionCall::~FunctionCall() {

}

IRConstant FunctionCall::getKind() const {
  return kind;
}

std::shared_ptr<FuncDefn> FunctionCall::getRefer() const {
  return refer;
}

bool FunctionCall::isPrev() {
  return isbuiltin && (builtinName == "Prev");
}

bool FunctionCall::isBuiltin() {
  return isbuiltin;
}

const std::string& FunctionCall::getBuiltinName() const {
  return builtinName;
}

bool FunctionCall::isTemporal() const {
  return istmp;
}

std::shared_ptr<Expr> FunctionCall::getTempVar() {
  return tmpvar;
}

void FunctionCall::processTemporal(const Ty* timety) {
  for (size_t i = 0; i < args.size(); ++i) {
    if (args[i]->getTyp() == timety) {
      istmp = true;
      tmpvar = args[i];
      args.erase(args.begin() + i);
      break;
    }
  }
}

void FunctionCall::print(FILE* file, int indent) const {
  fprintf(file, "%*sFunctionCall:\n", indent, "");
  fprintf(file, "%*sfun: %s\n", indent + 2, "", refer->toSignature().c_str());
  if (argSize()) {
    fprintf(file, "%*sargs:\n", indent + 2, "");
    for (size_t i = 0; i < argSize(); i++) {
      if (get(i) != nullptr) {
        get(i)->print(file, indent + 4);
      }
    }
  }
}

}
}
