#include "ArrayTy.h"

namespace swift {
namespace ir {
ArrayTy::ArrayTy(const Ty* base, int dim) :
    Ty(ir::IRConstant::ARRAY), base(base), dim(dim) {
}

ArrayTy::~ArrayTy() {
}

const Ty* ArrayTy::getBase() const {
  return base;
}

int ArrayTy::getDim() const {
  return dim;
}

std::string ArrayTy::toString() const {
  std::string ret;
  for (int i = 0; i < dim; i++)
    ret.append("std::vector<");
  ret.append(base->toString());
  for (int i = 0; i < dim; i++)
    ret.push_back('>');
  return ret;
}

}
}
