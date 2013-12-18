#pragma once
#include "ConstSymbol.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class InstSymbol :
  public swift::ir::ConstSymbol {
public:
  InstSymbol(TypeDomain* refer = NULL, int id = -1);
  virtual ~InstSymbol();

  TypeDomain* getRefer();
  int getID();
  bool isNull();

private:
  TypeDomain* refer;
  int id;
};

}
}