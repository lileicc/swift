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

private:
  IRConstant kind;
  std::shared_ptr<FuncDefn> refer;
};

}
}
