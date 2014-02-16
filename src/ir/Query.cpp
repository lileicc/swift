#include "Query.h"

namespace swift {
namespace ir {

Query::Query(std::shared_ptr<Expr> var, bool general) :
    var(var), general(general) {
}

Query::~Query() {
}

bool Query::isGeneral() const {
  return general;
}

bool Query::isSpecial() const {
  return !general;
}

const std::shared_ptr<Expr>& Query::getVar() const {
  return var;
}

void Query::print(FILE* file, int indent) {
  fprintf(file, "%*sQuery:\n", indent, "");
  getVar()->print(file, indent + 2);
}

}
}
