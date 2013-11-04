#pragma once
#include "Ty.h"

//#include "TypeDomain.h"

namespace swift { namespace ir {
class TypeDomain;

class NameTy :public Ty {
  TypeDomain* refer;
public:
  NameTy(TypeDomain* refer);
  virtual ~NameTy();

  TypeDomain* getRefer();
};

}
}