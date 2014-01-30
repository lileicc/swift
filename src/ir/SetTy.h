#pragma once
#include "Ty.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class SetTy: public swift::ir::Ty {
public:
  SetTy(const Ty* refer);
  virtual ~SetTy();

  const Ty* getRefer() const;

  virtual std::string toString() const;

private:
  const Ty* refer;
};

}
}
