#pragma once

#include<vector>

#include "Ty.h"

namespace swift {
namespace ir {

class ArrayTy :public swift::ir::Ty {
  std::vector<int> size;
  Ty* base;
public:
  ArrayTy(IRConstant typ, Ty* base, std::vector<int> size = std::vector<int>());
  virtual ~ArrayTy();

  Ty* getBase();
  int getSize();
  int getDim(int k);
  std::vector<int>& getAllDim();
};

}
}