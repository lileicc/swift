#include "ArrayTy.h"

namespace swift { namespace ir {
ArrayTy::ArrayTy(IRConstant typ, Ty* base, const std::vector<int>& size)
  :Ty(typ), base(base), size(size) {
}

ArrayTy::~ArrayTy() {
}

Ty* ArrayTy::getBase() {
  return base;
}

const std::vector<int>& ArrayTy::getAllDim() {
  return size;
}

size_t ArrayTy::getSize() {
  return size.size();
}

int ArrayTy::getDim(int k) {
  return size[k];
}

void ArrayTy::addDim(int d)  {
  size.push_back(d);
}

}
}