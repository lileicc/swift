#include "NumberStmt.h"
#include "OriginAttr.h"
#include "VarDecl.h"
#include "Clause.h"
#include "TypeDomain.h"

namespace swift {
namespace ir {
NumberStmt::NumberStmt(std::shared_ptr<TypeDomain> refer) :
    refer(refer) {
}

NumberStmt::~NumberStmt() {
}

size_t NumberStmt::size() const {
  return origin.size();
}

const std::vector<std::shared_ptr<VarDecl>>& NumberStmt::getAllVars() const {
  return var;
}

const OriginAttr* NumberStmt::getOrigin(size_t k) const {
  return origin[k];
}

const std::shared_ptr<VarDecl>& NumberStmt::getVar(size_t k) const {
  return var[k];
}

std::shared_ptr<TypeDomain> NumberStmt::getRefer() const {
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

void NumberStmt::print(FILE* file, int indent) {
  fprintf(file, "%*s(NumberStmt:\n", indent, "");
  fprintf(file, "%*s:TypeDomain: %s", indent + 2, refer->getName().c_str());

  fprintf(file, "%*s(origins:\n", indent + 2, "");
  for (size_t i = 0; i < size(); i++) {
    fprintf(file, "%*s %s\n", getOrigin(i)->getName().c_str());
  }
  fprintf(file, "%*s)\n", indent + 2, "");

  fprintf(file, "%*s(Variables:\n", indent + 2, "");
  for (size_t i = 0; i < size(); i++) {
    fprintf(file, "%*s%s\n", indent + 4, "", getVar(i)->toString().c_str());
  }
  fprintf(file, "%*s)\n", indent + 2, "");
  fprintf(file, "%*s(body:\n", indent + 2, "");
  body->print(file, indent + 4);
  fprintf(file, "%*s)\n", indent + 2, "");
  fprintf(file, "%*s)\n", indent, "");

}

}
}
