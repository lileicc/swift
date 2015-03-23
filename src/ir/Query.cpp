#include "Query.h"

namespace swift {
namespace ir {

Query::Query(std::shared_ptr<Expr> var, std::string strExpr, bool general) :
    var(var),  strExpr(strExpr), general(general) {
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

const std::string& Query::str() const {
  return strExpr;
}

void Query::print(FILE* file, int indent) {
  fprintf(file, "%*sQuery:\n", indent, "");
  getVar()->print(file, indent + 2);
}

}
}
