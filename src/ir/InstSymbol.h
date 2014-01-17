#pragma once
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class InstSymbol {
public:
  InstSymbol(TypeDomain* refer, size_t id);
  virtual ~InstSymbol();

  TypeDomain* getRefer() const ;
  size_t getID() const ;
private:
  TypeDomain* refer;
  size_t id;
};

}
}
