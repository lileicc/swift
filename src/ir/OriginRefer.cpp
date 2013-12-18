#include "OriginRefer.h"

namespace swift { namespace ir {

OriginRefer::OriginRefer(OriginAttr* refer, Expr* var)
  :refer(refer), var(var) {
}

OriginRefer::~OriginRefer() {
}

OriginAttr* OriginRefer::getRefer()  {
  return refer;
}

Expr* OriginRefer::getVar() {
  return var;
}

}
}