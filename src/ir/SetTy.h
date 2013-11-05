#pragma once
#include "Ty.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class SetTy :
  public swift::ir::Ty {
public:
  SetTy(Ty* refer);
  virtual ~SetTy();

  Ty* getRefer();

  virtual std::string toString();

private:
  Ty* refer;
};

}
}