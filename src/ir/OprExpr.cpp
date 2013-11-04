#include "OprExpr.h"

namespace swift { namespace ir {

OprExpr::OprExpr(IRConstant op)
  :op(op) {
}

OprExpr::~OprExpr() {
}

IRConstant OprExpr::getOp() {
  return op;
}

}
}