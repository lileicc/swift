#pragma once

#include "IRForwardDecl.h"
#include "Ty.h"

namespace swift { namespace ir {

class NameTy :public Ty {
public:
  NameTy(TypeDomain* refer);
  virtual ~NameTy();

  TypeDomain* getRefer();

private:
  TypeDomain* refer;
};

}
}