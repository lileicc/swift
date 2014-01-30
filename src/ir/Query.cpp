#include "Query.h"

namespace swift {
namespace ir {

Query::Query(std::shared_ptr<Expr> var) :
    var(var) {
}

Query::~Query() {
}

const std::shared_ptr<Expr>& Query::getVar() const {
  return var;
}

void Query::print(FILE* file, int indent) {
  fprintf(file, "%*s(Query:\n", indent, "");
  getVar()->print(file, indent + 2);
  fprintf(file, "%*s)\n", indent, "");
}

}
}
