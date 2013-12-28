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

const std::vector<std::shared_ptr<VarDecl>>& NumberStmt::getAllVars() const {
  return var;
}

const OriginAttr* NumberStmt::getOrigin(int k) const {
  return origin[k];
}

const std::shared_ptr<VarDecl>& NumberStmt::getVar(int k) const {
  return var[k];
}

TypeDomain* NumberStmt::getRefer() const {
  return refer;
}

const std::shared_ptr<Clause>& NumberStmt::getBody() const {
  return body;
}

void NumberStmt::setBody(std::shared_ptr<Clause> c) {
  body = c;
}

void NumberStmt::addArg(const OriginAttr* o, std::string v) {
  origin.push_back(o);
  var.push_back(std::shared_ptr<VarDecl>(new VarDecl(o->getTyp(), v)));
}

}
}