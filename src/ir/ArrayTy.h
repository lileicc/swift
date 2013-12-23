#pragma once

#include<vector>

#include "IRForwardDecl.h"
#include "Ty.h"

namespace swift {
namespace ir {

class ArrayTy :public swift::ir::Ty {
public:
  ArrayTy(IRConstant typ, const Ty* base, int dim);
  virtual ~ArrayTy();

  const Ty* getBase() const;
  int getDim() const ;
  
  virtual std::string toString();

private:
  const Ty* base;
  int dim;
};

}
}
