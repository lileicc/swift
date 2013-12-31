#include "Query.h"

namespace swift { namespace ir {

Query::Query(std::shared_ptr<Expr> var)
  :var(var) {
}

Query::~Query() {
}

const std::shared_ptr<Expr>& Query::getVar() const {
  return var;
}

}
}