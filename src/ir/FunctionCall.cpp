#include "FunctionCall.h"

#include "FuncDefn.h"
#include "IRConst.h"

#include "../predecl/PreDecl.h"

namespace swift {
namespace ir {

// init for builtin functions
FunctionCall::FunctionCall(const predecl::PreDecl* refer) :
    refer(nullptr), builtin(refer), kind(IRConstant::FIXED), istmp(false), tmparg(nullptr) {
}

FunctionCall::FunctionCall(std::shared_ptr<FuncDefn> refer) :
    refer(refer), istmp(false), tmparg(nullptr), builtin(NULL) {
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

bool FunctionCall::isBuiltin() const {
  return builtin != NULL;
}

IRConstant FunctionCall::getKind() const {
  return kind;
}

std::shared_ptr<FuncDefn> FunctionCall::getRefer() const {
  return refer;
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
  fprintf(file, "%*sfun: %s\n", indent + 2, "", (refer != nullptr ? refer->toSignature().c_str() : ("[built-in] " + builtin->getName()).c_str()));
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
