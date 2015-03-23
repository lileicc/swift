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
  /**
   * is this FunctionCall has temporal argument
   * Note the underlying function should be temporal as well
   * @return
   */
  bool isTemporal() const;
  /**
   * get the argument for the temporal part
   * @return
   */
  std::shared_ptr<Expr> getTemporalArg();
  void processTemporal(const Ty* timety);

  // Builtin Function
  const predecl::PreDecl* getBuiltinRefer() const;
  bool isBuiltin() const;

private:
  std::shared_ptr<FuncDefn> refer;

  // TimeStep Features
  bool istmp;
  std::shared_ptr<Expr> tmparg;

  // Builtin Function Refer
  const predecl::PreDecl* builtin;

  IRConstant kind;
};

}
}
