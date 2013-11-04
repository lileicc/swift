#pragma once
#include "Ty.h"

#include "TypeDomain.h"

namespace swift { namespace ir {

class NameTy :public swift::ir::Ty {
  TypeDomain* refer;
public:
  NameTy(TypeDomain* refer);
  virtual ~NameTy();

  TypeDomain* getRefer();
};

}
}