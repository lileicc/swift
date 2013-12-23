#include "Query.h"

#include "VoidFuncCall.h"

namespace swift { namespace ir {

Query::Query(std::shared_ptr<FunctionCall> var)
  :var(var) {
}

Query::~Query() {
}

const std::shared_ptr<FunctionCall>& Query::getVar() const {
  return var;
}

}
}