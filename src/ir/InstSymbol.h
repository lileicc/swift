#pragma once
#include <memory>
#include "IRForwardDecl.h"

namespace swift { namespace ir {
class InstSymbol {
public:
  InstSymbol(std::shared_ptr<TypeDomain> refer, size_t id);
  virtual ~InstSymbol();

  std::shared_ptr<TypeDomain> getRefer() const ;
  size_t getID() const ;
private:
  std::shared_ptr<TypeDomain> refer;
  size_t id;
};

}
}
