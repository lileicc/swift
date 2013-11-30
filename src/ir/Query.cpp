#include "Query.h"

namespace swift { namespace ir {

  Query::Query(std::shared_ptr<FunctionCall> var)
  :var(var) {
}

Query::~Query() {
}

std::shared_ptr<FunctionCall> Query::getVar() {
  return var;
}

}
}