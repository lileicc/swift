#pragma once
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class InstSymbol {
public:
  InstSymbol(TypeDomain* refer = NULL, int id = -1);
  virtual ~InstSymbol();

  TypeDomain* getRefer() const ;
  int getID() const ;
  bool isNull() const ;

private:
  TypeDomain* refer;
  int id;
};

}
}
