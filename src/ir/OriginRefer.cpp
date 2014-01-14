#include "OriginRefer.h"

namespace swift { namespace ir {

OriginRefer::OriginRefer(const OriginAttr* refer, std::shared_ptr<Expr> var)
  :refer(refer), var(var) {
}

OriginRefer::~OriginRefer() {
}

const OriginAttr* OriginRefer::getRefer() const {
  return refer;
}

const std::shared_ptr<Expr>& OriginRefer::getVar() const {
  return var;
}

}
}