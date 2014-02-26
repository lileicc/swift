#pragma once
#include <memory>
#include "Expr.h"
#include "IRConst.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class FunctionCall: public swift::ir::Expr {
public:
  FunctionCall(std::shared_ptr<FuncDefn> refer);
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

  // TODO: Fix this!!!
  // Hacking Implementation of Prev() --> built-in function
  bool isPrev();
  bool isBuiltin();
  const std::string& getBuiltinName() const;
  FunctionCall(std::string name);

private:
  IRConstant kind;
  std::shared_ptr<FuncDefn> refer;

  // TimeStep Features
  bool istmp;
  std::shared_ptr<Expr> tmparg;
  // TODO: Fix this!
  // Hacking Implementation of BuiltinFunction
  bool isbuiltin;
  std::string builtinName;
};

}
}
