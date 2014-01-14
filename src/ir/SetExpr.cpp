#include "SetExpr.h"

namespace swift { namespace ir {

SetExpr::SetExpr(IRConstant kind)
  :kind(kind) {
}

SetExpr::~SetExpr() {
}

IRConstant SetExpr::getKind() const {
  return kind;
}

}
}