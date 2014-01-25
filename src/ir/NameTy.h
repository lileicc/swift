#pragma once
#include <memory>
#include "IRForwardDecl.h"
#include "Ty.h"

namespace swift { namespace ir {

class NameTy :public Ty {
public:
  NameTy(std::shared_ptr<TypeDomain> refer);
  virtual ~NameTy();

  std::shared_ptr<TypeDomain> getRefer() const;

  virtual std::string toString() const;

private:
  std::shared_ptr<TypeDomain> refer;
};

}
}
