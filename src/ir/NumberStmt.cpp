#include "NumberStmt.h"
#include "OriginAttr.h"
#include "VarDecl.h"

namespace swift { namespace ir {
NumberStmt::NumberStmt(TypeDomain* refer)
  :refer(refer) {
}

NumberStmt::~NumberStmt() {
}

size_t NumberStmt::size() {
  return origin.size();
}

OriginAttr* NumberStmt::getOrigin(int k)  {
  return origin[k];
}

VarDecl* NumberStmt::getVar(int k) {
  return var[k];
}

TypeDomain* NumberStmt::getRefer() {
  return refer;
}

void NumberStmt::addArg(OriginAttr* o, std::string v) {
  origin.push_back(o);
  var.push_back(new VarDecl(o->getTyp(), v));
}

}
}