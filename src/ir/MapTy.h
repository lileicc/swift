#pragma once

#include "IRForwardDecl.h"
#include "Ty.h"

namespace swift {
namespace ir {

class MapTy :public swift::ir::Ty {
public:
  MapTy(IRConstant typ, Ty* from, Ty* to);
  virtual ~MapTy();

  Ty* getFrom();
  Ty* getTo();

  virtual std::string toString();

private:
  Ty* from;
  Ty* to;
};

}
}