#pragma once

#include<vector>

#include "IRForwardDecl.h"
#include "Ty.h"

namespace swift {
namespace ir {

class ArrayTy :public swift::ir::Ty {
public:
  ArrayTy(IRConstant typ, Ty* base, const std::vector<int>& size = std::vector<int>());
  virtual ~ArrayTy();

  Ty* getBase();
  size_t getSize();
  int getDim(int k);
  void addDim(int d);
  const std::vector<int>& getAllDim();

  virtual std::string toString();

private:
  Ty* base;
  std::vector<int> size;
};

}
}
