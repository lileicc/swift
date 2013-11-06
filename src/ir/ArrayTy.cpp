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

std::string ArrayTy::toString() {
  std::string ret;
  for (size_t i = 0; i<size.size(); i++)
    ret.append("std::array<");
  ret.append(base->toString());
  for (size_t i = size.size() - 1; i >= 0; i--) {
    ret.push_back(',');
    ret.append(std::to_string(size[i]));
    ret.push_back('>');
  }
  return ret;
}

}
}
