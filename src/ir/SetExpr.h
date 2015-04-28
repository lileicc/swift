#pragma once
#include "Expr.h"
#include "IRConst.h"

namespace swift {
namespace ir {

class SetExpr: public swift::ir::Expr {
public:
  SetExpr(IRConstant kind);
  virtual ~SetExpr();

  IRConstant getKind() const;
  virtual void print(FILE* file, int indent) const;
  std::string toString();
private:
  IRConstant kind;
};

}
}
