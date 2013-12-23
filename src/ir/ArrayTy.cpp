#include "ArrayTy.h"

namespace swift { namespace ir {
ArrayTy::ArrayTy(IRConstant typ, const Ty* base, int dim)
  :Ty(typ), base(base), dim(dim) {
}

ArrayTy::~ArrayTy() {
}

const Ty* ArrayTy::getBase() const {
  return base;
}

int ArrayTy::getDim() const {
  return dim;
}

std::string ArrayTy::toString() {
  std::string ret;
  for (int i = 0; i<dim; i++)
    ret.append("std::vector<");
  ret.append(base->toString());
  for (int i = 0; i<dim; i++)
    ret.push_back('>');
  return ret;
}

}
}
