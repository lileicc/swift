#pragma once

#include "Expr.h"
#include "IRConst.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class ConstSymbol: public swift::ir::Expr {
public:
  ConstSymbol(IRConstant typ);
  virtual ~ConstSymbol();

  IRConstant getKind() const;

  virtual void print(FILE* file, int indent) const;

private:
  IRConstant kind;
};

}
}
