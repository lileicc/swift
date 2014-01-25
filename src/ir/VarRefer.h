#pragma once
#include <memory>
#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class VarRefer :
  public swift::ir::Expr {
public:
  VarRefer(std::shared_ptr<VarDecl> refer = NULL);
  virtual ~VarRefer();

  std::shared_ptr<VarDecl> getRefer() const;
  void print(FILE* file, int indent);

private:
  std::shared_ptr<VarDecl> refer;
};

}
}