#include "Query.h"

#include "VoidFuncCall.h"

namespace swift { namespace ir {

Query::Query(VoidFuncCall* var)
  :var(var) {
}

Query::~Query() {
}

VoidFuncCall* Query::getVar() {
  return var;
}

}
}