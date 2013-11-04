#include "ArrayTy.h"

namespace swift { namespace ir {
ArrayTy::ArrayTy(IRConstant typ, Ty* base, std::vector<int>size)
  :Ty(typ), base(base), size(size) {
}

ArrayTy::~ArrayTy() {
}

Ty* ArrayTy::getBase() {
  return base;
}

std::vector<int>& ArrayTy::getAllDim() {
  return size;
}

int ArrayTy::getSize() {
  return size.size();
}

int ArrayTy::getDim(int k) {
  return size[k];
}

}
}