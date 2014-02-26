#pragma once
#include <memory>
#include "Expr.h"
#include "IRConst.h"
#include "IRForwardDecl.h"

// Forward Declaration
namespace swift {
namespace predecl {
  class PreDecl;
}
}

namespace swift {
namespace ir {

class FunctionCall: public swift::ir::Expr {
public:
  FunctionCall(std::shared_ptr<FuncDefn> refer);
  FunctionCall(const predecl::PreDecl* refer);
  virtual ~FunctionCall();

  IRConstant getKind() const;
  std::shared_ptr<FuncDefn> getRefer() const;
  void print(FILE* file, int indent) const;

  // TimeStep Features
  bool isTemporal() const;
  std::shared_ptr<Expr> getTempVar();
  void processTemporal(const Ty* timety);

  // Builtin Function
  const predecl::PreDecl* getBuiltinRefer() const;
  bool isBuiltin() const;

private:
  IRConstant kind;
  std::shared_ptr<FuncDefn> refer;

  // TimeStep Features
  bool istmp;
  std::shared_ptr<Expr> tmpvar;

  // Builtin Function Refer
  const predecl::PreDecl* builtin;
};

}
}
