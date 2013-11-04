#pragma once

#include "IRForwardDecl.h"

#include "Ty.h"

namespace swift { namespace ir {

class NameTy :public Ty {
  TypeDomain* refer;
public:
  NameTy(TypeDomain* refer);
  virtual ~NameTy();

  TypeDomain* getRefer();
};

}
}