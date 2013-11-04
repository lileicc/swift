#pragma once

#include "IRForwardDecl.h"

#include "Ty.h"

namespace swift {
namespace ir {

class MapTy :public swift::ir::Ty {
  Ty* from;
  Ty* to;
public:
  MapTy(IRConstant typ, Ty* from, Ty* to);
  virtual ~MapTy();

  Ty* getFrom();
  Ty* getTo();
};

}
}